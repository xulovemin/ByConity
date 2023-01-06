
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

#include <IO/Operators.h>
#include <Parsers/ASTShowWarehousesQuery.h>
#include <Parsers/ASTSetQuery.h>

#include <sstream>

namespace DB
{

ASTPtr ASTShowWarehousesQuery::clone() const
{
    auto res = std::make_shared<ASTShowWarehousesQuery>(*this);
    res->children.clear();

    if (!like.empty())
        res->like = like;

    return res;

}
void ASTShowWarehousesQuery::formatImpl(const FormatSettings & s, FormatState &/*state*/, FormatStateStacked /*frame*/) const
{
    s.ostr << (s.hilite ? hilite_keyword : "")
           << "SHOW WAREHOUSES "
           << (s.hilite ? hilite_none : "");

    if (!like.empty())
    {
        std::stringstream ss;
        ss << std::quoted(like, '\'');
        s.ostr << (s.hilite ? hilite_keyword : "")
               << "LIKE "
               << (s.hilite ? hilite_none : "")
               << ss.str();
    }

}

}
