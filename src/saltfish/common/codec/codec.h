// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once
#include "saltfish/util/status.h"

namespace saltfish {
namespace common {

static const uint8_t INTERNAL_VALUE_RESERVED_LEN = 1;
/* Reserved/1 byte, Timestamp/8 byte*/
static const uint8_t INTERNAL_VALUE_HEAD_LEN = 9;

static std::string EncodeValue(const Slice &user_value, uint64_t ts);
static std::string DecodeValue(Slice &internal_value, uint64_t *ts);

}
}