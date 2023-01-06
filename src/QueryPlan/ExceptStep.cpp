
/*
 * Copyright (2022) ByteDance Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <QueryPlan/ExceptStep.h>

#include <Core/Block.h>
#include <Interpreters/Context.h>

namespace DB
{
ExceptStep::ExceptStep(
    DataStreams input_streams_,
    DataStream output_stream_,
    std::unordered_map<String, std::vector<String>> output_to_inputs_,
    bool distinct_)
    : SetOperationStep(input_streams_, output_stream_, output_to_inputs_), distinct(distinct_)
{
}

void ExceptStep::setInputStreams(const DataStreams & input_streams_)
{
    input_streams = input_streams_;
}

QueryPipelinePtr ExceptStep::updatePipeline(QueryPipelines, const BuildQueryPipelineSettings &)
{
    throw Exception("ExceptStep should be rewritten into UnionStep", ErrorCodes::NOT_IMPLEMENTED);
}

void ExceptStep::serialize(WriteBuffer &) const
{
    throw Exception("ExceptStep should be rewritten into UnionStep", ErrorCodes::NOT_IMPLEMENTED);
}

QueryPlanStepPtr ExceptStep::deserialize(ReadBuffer &, ContextPtr)
{
    throw Exception("ExceptStep should be rewritten into UnionStep", ErrorCodes::NOT_IMPLEMENTED);
}

bool ExceptStep::isDistinct() const
{
    return distinct;
}

std::shared_ptr<IQueryPlanStep> ExceptStep::copy(ContextPtr) const
{
    return std::make_unique<ExceptStep>(input_streams, output_stream.value(), distinct);
}
}
