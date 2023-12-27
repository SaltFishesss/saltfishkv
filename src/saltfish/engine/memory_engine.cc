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

#include "saltfish/engine/memory_engine.h"

#include "saltfish/common/codec/codec.h"

namespace saltfish {
namespace engine {

Status MemoryEngine::Get(const Slice &user_key, std::string *user_value) {
  std::shared_lock<std::shared_mutex> r_lock(rw_lock_);
  auto iter = kv_map_.find(user_key.ToString());
  if (iter == kv_map_.cend()) {
    return Status::NotFound("Key not found");
  }
  uint64_t ts;
  Slice internal_value{iter->second.data(), iter->second.size()};
  *user_value = common::DecodeValue(internal_value, &ts);
  return Status::OK();
}

Status MemoryEngine::Put(const Slice &user_key, Slice &user_value) {
  auto internal_key = user_key.ToString();
  auto internal_value = common::EncodeValue(user_value, 0);
  std::unique_lock<std::shared_mutex> r_lock(rw_lock_);
  kv_map_.insert(std::make_pair(internal_key, internal_value));
  return Status::OK();
}

Status MemoryEngine::Delete(const Slice &user_key) {
  std::unique_lock<std::shared_mutex> r_lock(rw_lock_);
  auto iter = kv_map_.find(user_key.ToString());
  if (iter == kv_map_.cend()) {
    return Status::NotFound("Key not found");
  }
  kv_map_.erase(iter);
  return Status::OK();
}
}
}