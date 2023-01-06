
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
#include <Parsers/IAST_fwd.h>
#include <Parsers/CommonParsers.h>
#include <Parsers/ASTDictionaryAttributeDeclaration.h>
#include <Parsers/ASTIdentifier.h>


namespace DB
{
/// Parser for dictionary attribute declaration, similar with parser for table
/// column, but attributes has less parameters. Produces
/// ASTDictionaryAttributeDeclaration.
class ParserDictionaryAttributeDeclaration : public IParserDialectBase
{
protected:
    const char * getName() const override { return "attribute declaration"; }

    bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;
public:
    using IParserDialectBase::IParserDialectBase;
};


/// Creates ASTExpressionList consists of dictionary attributes declaration.
class ParserDictionaryAttributeDeclarationList : public IParserDialectBase
{
protected:
    const char * getName() const  override{ return "attribute declaration list"; }
    bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;
public:
    using IParserDialectBase::IParserDialectBase;
};

}
