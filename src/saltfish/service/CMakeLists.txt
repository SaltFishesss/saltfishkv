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

PROTOBUF_GENERATE_CPP(
        KV_SERVICE_PROTO_SRCS KV_SERVICE_PROTO_HDRS KV_SERVICE_PROTO_TGTS
        SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..
        BINARY_ROOT ${CMAKE_CURRENT_BINARY_DIR}/../..
        PROTO_FILES kv_service.proto common.proto)
set(SERVICE_PROTO_LIBS protobuf)
ADD_EXPORTABLE_LIBRARY(kv_service_proto
        SRCS ${KV_SERVICE_PROTO_SRCS}
        DEPS ${SERVICE_PROTO_LIBS}
        NONLINK_DEPS ${KV_SERVICE_PROTO_TGTS})

set(KV_SERVICE_SRCS kv_service.cc)
set(KV_SERVICE_LIBS
    kv_service_proto
    ${SERVICE_PROTO_LIBS}
    )
ADD_EXPORTABLE_LIBRARY(kv_service
        SRCS ${KV_SERVICE_SRCS}
        DEPS ${KV_SERVICE_LIBS})

