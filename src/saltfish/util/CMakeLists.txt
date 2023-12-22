# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

#######################################
# protoc-gen-insertions
#######################################

add_executable(protoc-gen-insertions protoc_gen_insertions.cc)
target_link_libraries(protoc-gen-insertions gutil protobuf protoc ${SALTFISH_BASE_LIBS})


#######################################
# saltfish_util
#######################################

set(UTIL_SRCS
  slice.cc
  status.cc
  malloc.cc
)

set(UTIL_LIBS
  gflags
  glog
)


ADD_EXPORTABLE_LIBRARY(util
  SRCS ${UTIL_SRCS}
  DEPS ${UTIL_LIBS}
  NONLINK_DEPS
  EXPORTED_DEPS ${EXPORTED_UTIL_LIBS})