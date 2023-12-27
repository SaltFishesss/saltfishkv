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

#include "saltfish/common/codec/codec.h"

#include <glog/logging.h>

namespace saltfish {
namespace common {

extern std::string EncodeValue(const Slice &user_value, uint64_t ts) {
  std::string internal_value;
  internal_value.reserve(INTERNAL_VALUE_HEAD_LEN + user_value.size());
  internal_value.append(reinterpret_cast<char *>(&ts), sizeof(ts));
  internal_value.append(user_value.data(), user_value.data());
  return internal_value;
}

extern std::string DecodeValue(Slice &internal_value, uint64_t *ts) {
  CHECK_GE(internal_value.size(), INTERNAL_VALUE_HEAD_LEN) << "Data corrupted when decode value:"
                                                           << internal_value.ToDebugString();
  internal_value.remove_prefix(INTERNAL_VALUE_HEAD_LEN);
  memcpy(ts, internal_value.data(), sizeof(uint64_t));
  internal_value.remove_prefix(sizeof(uint64_t));
  return internal_value.ToString();
}

}
}