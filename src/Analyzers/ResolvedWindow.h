
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

#include <Parsers/ASTWindowDefinition.h>

namespace DB
{

struct ResolvedWindow;

using ResolvedWindowPtr = std::shared_ptr<ResolvedWindow>;

struct ResolvedWindow
{
    const ASTWindowDefinition * origin_ast;
    ASTPtr partition_by;
    ASTPtr order_by;
    WindowFrame frame;
};

// Resolve an ASTWindowDefinition to a ResolvedWindow by
//   1. combine inherited properties if a parent window name exists
//   2. evaluate boundary offset values
// See also: `ExpressionAnalyzer::makeWindowDescriptionFromAST`
ResolvedWindowPtr resolveWindow(const ASTPtr & node,
                                const std::unordered_map<String, ResolvedWindowPtr> & registered_windows,
                                ContextPtr context);
}
