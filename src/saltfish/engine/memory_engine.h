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

#include "saltfish/engine/engine.h"

#include <shared_mutex>

namespace saltfish {
namespace engine {
class MemoryEngine : public Engine {
 public:
  MemoryEngine() = default;
  ~MemoryEngine() override = default;
  DISALLOW_COPY_AND_ASSIGN(MemoryEngine);

  Status Init(EngineOptions opt) override { return Status::OK(); };
  Status Close() override { return Status::OK(); };

  Status Get(const Slice &user_key, std::string *user_value) override;
  Status Put(const Slice &user_key, Slice &user_value) override;
  Status Delete(const Slice &user_key) override;

  Status LoadSnapshot(std::shared_ptr<Snapshot> snapshot) override {
    return Status::OK();
  }
  Snapshot *NewSnapshot() override { return nullptr; }

  Status Drop() override { return Status::OK(); }

 private:
  mutable std::shared_mutex rw_lock_;

  std::map<std::string, std::string> kv_map_;
};

}
}
