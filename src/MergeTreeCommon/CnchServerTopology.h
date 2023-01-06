
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

#include <list>
#include <DataTypes/DataTypeUUID.h>
#include <Common/HostWithPorts.h>
#include <DataTypes/DataTypeString.h>

namespace DB
{

class CnchServerTopology
{

public:
    CnchServerTopology(const UInt64 & lease_expiration_, HostWithPortsVec && servers_);

    HostWithPortsVec getServerList() const;
    size_t getServerSize() const;

    void setExpiration(const UInt64 & new_expiration);

    UInt64 getExpiration() const;

    String format() const;

private:
    UInt64 lease_expiration;
    HostWithPortsVec servers;
};


String dumpTopologies(const std::list<CnchServerTopology>& topologies);

}

