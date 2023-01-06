
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
 * This file may have been modified by ByteDance Ltd. (“ Bytedance's Modifications”).
 * All Bytedance's Modifications are Copyright (2023) ByteDance Ltd..
 */

#include <gtest/gtest.h>
#include <IO/ReadHelpers.h>
#include <IO/WriteHelpers.h>
#include "gtest_disk.h"


#define RUN_HDFS_TEST 0
#if RUN_HDFS_TEST

#include <Disks/HDFS/DiskHDFS.h>
#include <Poco/Util/XMLConfiguration.h>

const String hdfs_uri = "hdfs://172.20.0.2:9000/disk_test/";
const String metadata_path = "/path/to/metadata/";
const String config_path = "/path/to/config.xml";
const String file_name = "test.txt";


TEST(DiskTestHDFS, RemoveFileHDFS)
{
    Poco::Util::AbstractConfiguration *config = new Poco::Util::XMLConfiguration(config_path);
    auto settings = std::make_unique<DB::DiskHDFSSettings>(1024 * 1024);
    auto disk = DB::DiskHDFS("disk_hdfs", hdfs_uri, std::move(settings), metadata_path, *config);

    DB::HDFSBuilderWrapper builder = DB::createHDFSBuilder(hdfs_uri, *config);
    DB::HDFSFSPtr fs = DB::createHDFSFS(builder.get());

    disk.writeFile(file_name, {.buffer_size = 1024, .mode = DB::WriteMode::Rewrite});
    auto metadata = disk.readMeta(file_name);

    const String hdfs_file_name = metadata.remote_fs_objects[0].first;
    const String hdfs_file_path = "/disk_test/" + hdfs_file_name;

    auto ret = hdfsExists(fs.get(), hdfs_file_path.data());
    EXPECT_EQ(0, ret);

    disk.removeFile(file_name);
    ret = hdfsExists(fs.get(), hdfs_file_path.data());
    EXPECT_EQ(-1, ret);
}


TEST(DiskTestHDFS, WriteReadHDFS)
{
    Poco::Util::AbstractConfiguration *config = new Poco::Util::XMLConfiguration(config_path);
    auto settings = std::make_unique<DB::DiskHDFSSettings>(1024 * 1024);
    auto disk = DB::DiskHDFS("disk_hdfs", hdfs_uri, std::move(settings), metadata_path, *config);

    {
        auto out = disk.writeFile(file_name, {.buffer_size = 1024, .mode = DB::WriteMode::Rewrite});
        writeString("Test write to file", *out);
    }

    {
        DB::String result;
        auto in = disk.readFile(file_name, {.buffer_size = 1024, .estimated_size = 1024, .aio_threshold = 1024, .mmap_threshold = 1024});
        readString(result, *in);
        EXPECT_EQ("Test write to file", result);
    }

    disk.removeFileIfExists(file_name);
}


TEST(DiskTestHDFS, RewriteFileHDFS)
{
    Poco::Util::AbstractConfiguration *config = new Poco::Util::XMLConfiguration(config_path);
    auto settings = std::make_unique<DB::DiskHDFSSettings>(1024 * 1024);
    auto disk = DB::DiskHDFS("disk_hdfs", hdfs_uri, std::move(settings), metadata_path, *config);

    for (size_t i = 1; i <= 10; ++i)
    {
        std::unique_ptr<DB::WriteBuffer> out = disk.writeFile(file_name, {.buffer_size = 1024, .mode = DB::WriteMode::Rewrite});
        writeString("Text" + DB::toString(i), *out);
    }

    {
        String result;
        auto in = disk.readFile(file_name, {.buffer_size = 1024, .estimated_size = 1024, .aio_threshold = 1024, .mmap_threshold = 1024});
        readString(result, *in);
        EXPECT_EQ("Text10", result);
        readString(result, *in);
        EXPECT_EQ("", result);
    }

    disk.removeFileIfExists(file_name);
}


TEST(DiskTestHDFS, AppendFileHDFS)
{
    Poco::Util::AbstractConfiguration *config = new Poco::Util::XMLConfiguration(config_path);
    auto settings = std::make_unique<DB::DiskHDFSSettings>(1024 * 1024);
    auto disk = DB::DiskHDFS("disk_hdfs", hdfs_uri, std::move(settings), metadata_path, *config);

    {
        std::unique_ptr<DB::WriteBuffer> out = disk.writeFile(file_name, {.buffer_size = 1024, .mode = DB::WriteMode::Append});
        writeString("Text", *out);
        for (size_t i = 0; i < 10; ++i)
        {
            writeIntText(i, *out);
        }
    }

    {
        String result, expected;
        auto in = disk.readFile(file_name, {.buffer_size = 1024, .estimated_size = 1024, .aio_threshold = 1024, .mmap_threshold = 1024});

        readString(result, *in);
        EXPECT_EQ("Text0123456789", result);

        readString(result, *in);
        EXPECT_EQ("", result);
    }

    disk.removeFileIfExists(file_name);
}


TEST(DiskTestHDFS, SeekHDFS)
{
    Poco::Util::AbstractConfiguration *config = new Poco::Util::XMLConfiguration(config_path);
    auto settings = std::make_unique<DB::DiskHDFSSettings>(1024 * 1024);
    auto disk = DB::DiskHDFS("disk_hdfs", hdfs_uri, std::move(settings), metadata_path, *config);

    {
        std::unique_ptr<DB::WriteBuffer> out = disk.writeFile(file_name, {.buffer_size = 1024, .mode = DB::WriteMode::Rewrite});
        writeString("test data", *out);
    }

    /// Test SEEK_SET
    {
        String buf(4, '0');
        std::unique_ptr<DB::SeekableReadBuffer> in = disk.readFile(file_name, {.buffer_size = 1024, .estimated_size = 1024, .aio_threshold = 1024, .mmap_threshold = 1024});

        in->seek(5, SEEK_SET);

        in->readStrict(buf.data(), 4);
        EXPECT_EQ("data", buf);
    }

    /// Test SEEK_CUR
    {
        std::unique_ptr<DB::SeekableReadBuffer> in = disk.readFile(file_name, {.buffer_size = 1024, .estimated_size = 1024, .aio_threshold = 1024, .mmap_threshold = 1024});
        String buf(4, '0');

        in->readStrict(buf.data(), 4);
        EXPECT_EQ("test", buf);

        // Skip whitespace
        in->seek(1, SEEK_CUR);

        in->readStrict(buf.data(), 4);
        EXPECT_EQ("data", buf);
    }

    disk.removeFileIfExists(file_name);
}

#endif
