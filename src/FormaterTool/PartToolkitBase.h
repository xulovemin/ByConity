
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
#include <Parsers/IAST_fwd.h>
#include <Storages/IStorage_fwd.h>
#include <Storages/StorageMergeTree.h>
#include <Interpreters/Context_fwd.h>
#include <unordered_map>
#include <Core/Field.h>

namespace DB
{

#define PT_RELATIVE_LOCAL_PATH "data/"

class PartToolkitBase : public WithMutableContext
{

public:
    PartToolkitBase(const ASTPtr & query_ptr_, ContextMutablePtr context_);

    virtual void execute() = 0;

    virtual ~PartToolkitBase();

protected:
    void applySettings();

    StoragePtr getTable();

    PartNamesWithDisks collectPartsFromSource(const String & source_dirs_str, const String & dest_dir);

    const ASTPtr & query_ptr;
    std::unordered_map<String, Field> user_settings;

private:
    StoragePtr storage = nullptr;

};

}
