
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

#pragma once

#include <Parsers/ASTSetQuery.h>
#include <Parsers/ExpressionElementParsers.h>
#include <Parsers/IParserBase.h>
#include <Parsers/ParserQueryWithOutput.h>

namespace DB
{
/** Query Reproduce
 * Syntax is as follows:
 * Reproduce /path/of/query_id.zip
 */
class ParserReproduceQuery : public IParserDialectBase
{
protected:
    const char * end;
    const char * getName() const override{ return "REPRODUCE query"; }
    bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;

public:
    ParserReproduceQuery(const char * end_) : end(end_) { }
};
}
