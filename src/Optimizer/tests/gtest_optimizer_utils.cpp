
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

#include <Analyzers/ASTEquals.h>
#include <Optimizer/Utils.h>

#include <Parsers/ASTFunction.h>
#include <Parsers/ASTIdentifier.h>
#include <Parsers/ASTLiteral.h>
#include <Parsers/formatAST.h>

#include <gtest/gtest.h>

using namespace DB;

void checkAstTreeEquals(const ASTPtr & left, const ASTPtr & right, bool expect)
{
    if (expect != ASTEquality::compareTree(left, right))
        GTEST_FAIL() << "AST equal check fails, left: " << serializeAST(*left) << ", right: " << serializeAST(*right)
                     << ", expect: " << expect << std::endl;
}

TEST(OptimizerUtils, AstTreeEquals)
{
    using std::make_shared;

    checkAstTreeEquals(make_shared<ASTLiteral>("a"), make_shared<ASTIdentifier>("a"), false);
    checkAstTreeEquals(make_shared<ASTLiteral>(1L), make_shared<ASTLiteral>(1U), false);
    checkAstTreeEquals(makeASTFunction("foo"), makeASTFunction("bar"), false);
    checkAstTreeEquals(makeASTFunction("foo"), makeASTFunction("foo"), true);
    checkAstTreeEquals(makeASTFunction("foo", make_shared<ASTLiteral>(1L)), makeASTFunction("foo", make_shared<ASTLiteral>(1U)), false);
    checkAstTreeEquals(makeASTFunction("foo", make_shared<ASTLiteral>(1L)), makeASTFunction("foo", make_shared<ASTLiteral>(1L)), true);
    checkAstTreeEquals(
        makeASTFunction("foo", make_shared<ASTLiteral>(1L), make_shared<ASTLiteral>(2L)),
        makeASTFunction("foo", make_shared<ASTLiteral>(2L), make_shared<ASTLiteral>(1L)),
        false);
    checkAstTreeEquals(
        makeASTFunction("foo", make_shared<ASTLiteral>(1L), makeASTFunction("bar", make_shared<ASTIdentifier>("x"))),
        makeASTFunction("foo", make_shared<ASTLiteral>(1L), makeASTFunction("bar", make_shared<ASTIdentifier>("x"))),
        true);
}
