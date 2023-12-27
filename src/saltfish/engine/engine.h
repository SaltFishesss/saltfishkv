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

#include <iostream>
#include <memory>

#include "saltfish/util/status.h"

namespace saltfish {
namespace engine {

struct EngineOptions {
};

class Snapshot {
};

class Engine {
 public:
  Engine() = default;
  virtual ~Engine() = 0;

  virtual Status Init(EngineOptions opt) = 0;
  virtual Status Close() = 0;

  virtual Status Get(const Slice &user_key, std::string *user_value) = 0;
  virtual Status Put(const Slice &user_key, Slice &user_value) = 0;
  virtual Status Delete(const Slice &user_key) = 0;

  virtual Status LoadSnapshot(std::shared_ptr<Snapshot> snapshot) = 0;
  virtual Snapshot *NewSnapshot() = 0;

  virtual Status Drop() = 0;
};
}
}