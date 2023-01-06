
/*
 * Copyright 2016-2023 ClickHouse, Inc.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/*
 * This file may have been modified by Bytedance Ltd. and/or its affiliates (“ Bytedance's Modifications”).
 * All Bytedance's Modifications are Copyright (2023) Bytedance Ltd. and/or its affiliate and/or its affiliates.
 */

#include "OwnSplitChannel.h"

#include <iostream>
#include <Core/Block.h>
#include <Interpreters/InternalTextLogsQueue.h>
#include <Interpreters/TextLog.h>
#include <IO/WriteBufferFromFileDescriptor.h>
#include <sys/time.h>
#include <Poco/Message.h>
#include <Common/CurrentThread.h>
#include <Common/DNSResolver.h>
#include <common/getThreadId.h>
#include <Common/SensitiveDataMasker.h>
#include <Common/IO.h>

namespace DB
{
void OwnSplitChannel::log(const Poco::Message & msg)
{
    auto logs_queue = CurrentThread::getInternalTextLogsQueue();

    if (channels.empty() && (logs_queue == nullptr || msg.getPriority() > logs_queue->max_priority))
        return;

    if (auto * masker = SensitiveDataMasker::getInstance())
    {
        auto message_text = msg.getText();
        auto matches = masker->wipeSensitiveData(message_text);
        if (matches > 0)
        {
            tryLogSplit({msg, message_text}); // we will continue with the copy of original message with text modified
            return;
        }

    }

    tryLogSplit(msg);
}


void OwnSplitChannel::tryLogSplit(const Poco::Message & msg)
{
    try
    {
        logSplit(msg);
    }
    /// It is better to catch the errors here in order to avoid
    /// breaking some functionality because of unexpected "File not
    /// found" (or similar) error.
    ///
    /// For example StorageDistributedDirectoryMonitor will mark batch
    /// as broken, some MergeTree code can also be affected.
    ///
    /// Also note, that we cannot log the exception here, since this
    /// will lead to recursion, using regular tryLogCurrentException().
    /// but let's log it into the stderr at least.
    catch (...)
    {
        MemoryTracker::LockExceptionInThread lock_memory_tracker(VariableContext::Global);

        const std::string & exception_message = getCurrentExceptionMessage(true);
        const std::string & message = msg.getText();

        /// NOTE: errors are ignored, since nothing can be done.
        writeRetry(STDERR_FILENO, "Cannot add message to the log: ");
        writeRetry(STDERR_FILENO, message.data(), message.size());
        writeRetry(STDERR_FILENO, "\n");
        writeRetry(STDERR_FILENO, exception_message.data(), exception_message.size());
        writeRetry(STDERR_FILENO, "\n");
    }
}

void OwnSplitChannel::logSplit(const Poco::Message & msg)
{
    ExtendedLogMessage msg_ext = ExtendedLogMessage::getFrom(msg);

    /// Log data to child channels
    for (auto & channel : channels)
    {
        if (channel.second)
            channel.second->logExtended(msg_ext); // extended child
        else
            channel.first->log(msg); // ordinary child
    }

    auto logs_queue = CurrentThread::getInternalTextLogsQueue();

    /// Log to "TCP queue" if message is not too noisy
    if (logs_queue && msg.getPriority() <= logs_queue->max_priority)
    {
        MutableColumns columns = InternalTextLogsQueue::getSampleColumns();

        size_t i = 0;
        columns[i++]->insert(msg_ext.time_seconds);
        columns[i++]->insert(msg_ext.time_microseconds);
        columns[i++]->insert(DNSResolver::instance().getHostName());
        columns[i++]->insert(msg_ext.query_id);
        columns[i++]->insert(msg_ext.thread_id);
        columns[i++]->insert(Int64(msg.getPriority()));
        columns[i++]->insert(msg.getSource());
        columns[i++]->insert(msg.getText());

        [[maybe_unused]] auto push_result = logs_queue->emplace(std::move(columns));
    }

    /// Also log to system.text_log table, if message is not too noisy
    auto text_log_max_priority_loaded = text_log_max_priority.load(std::memory_order_relaxed);
    if (text_log_max_priority_loaded && msg.getPriority() <= text_log_max_priority_loaded)
    {
        TextLogElement elem;

        elem.event_time = msg_ext.time_seconds;
        elem.event_time_microseconds = msg_ext.time_in_microseconds;
        elem.microseconds = msg_ext.time_microseconds;

        elem.thread_name = getThreadName();
        elem.thread_id = msg_ext.thread_id;

        elem.query_id = msg_ext.query_id;

        elem.message = msg.getText();
        elem.logger_name = msg.getSource();
        elem.level = msg.getPriority();

        if (msg.getSourceFile() != nullptr)
            elem.source_file = msg.getSourceFile();

        elem.source_line = msg.getSourceLine();
        std::shared_ptr<TextLog> text_log_locked{};
        {
            std::lock_guard<std::mutex> lock(text_log_mutex);
            text_log_locked = text_log.lock();
        }
        if (text_log_locked)
            text_log_locked->add(elem);
    }
}


void OwnSplitChannel::addChannel(Poco::AutoPtr<Poco::Channel> channel)
{
    channels.emplace_back(std::move(channel), dynamic_cast<ExtendedLogChannel *>(channel.get()));
}

void OwnSplitChannel::addTextLog(std::shared_ptr<DB::TextLog> log, int max_priority)
{
    std::lock_guard<std::mutex> lock(text_log_mutex);
    text_log = log;
    text_log_max_priority.store(max_priority, std::memory_order_relaxed);
}

}
