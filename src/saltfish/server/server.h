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

#include "saltfish/util/status.h"

namespace saltfish {

struct ServerOption {
};

class Server {
 public:
  Server(const std::string name, const ServerOption &opt) : name_(name), option_(opt) {}
  ~Server() = default;

  virtual Status Init() = 0;
  virtual Status Start() = 0;
  virtual Status Shutdown() = 0;
 private:
  std::string name_;
  ServerOption option_;

  DISALLOW_COPY_AND_ASSIGN(Server);
};

}