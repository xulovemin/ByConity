
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

#pragma once

#include <Parsers/IParserBase.h>


namespace DB
{


class ParserProjectionSelectQuery : public IParserDialectBase
{
protected:
    const char * getName() const override { return "PROJECTION SELECT query"; }
    bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;
public:
    using IParserDialectBase::IParserDialectBase;
};

}
