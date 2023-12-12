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

cmake_minimum_required(VERSION 3.20.3)

project(SaltFish)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")
include(CMakeParseArguments)

set(THIRDPARTY_INSTALL_DIR ${THIRDPARTY_DIR}/installed)
message("Set Third party path: ${THIRDPARTY_INSTALL_DIR}")

############################################################
# Dependencies
############################################################
function(ADD_THIRDPARTY_LIB LIB_NAME)
    set(options)
    set(one_value_args SHARED_LIB STATIC_LIB)
    set(multi_value_args DEPS)
    cmake_parse_arguments(ARG "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})
    if(ARG_UNPARSED_ARGUMENTS)
        message(SEND_ERROR "Error: unrecognized arguments: ${ARG_UNPARSED_ARGUMENTS}")
    endif()

    if(("${SALT_FISH_LINK}" STREQUAL "s" AND ARG_STATIC_LIB) OR (NOT ARG_SHARED_LIB))
        if(NOT ARG_STATIC_LIB)
            message(FATAL_ERROR "No static or shared library provided for ${LIB_NAME}")
        endif()
        add_library(${LIB_NAME} STATIC IMPORTED)
        set_target_properties(${LIB_NAME}
                PROPERTIES IMPORTED_LOCATION "${ARG_STATIC_LIB}")
        message("Added static library dependency ${LIB_NAME}: ${ARG_STATIC_LIB}")
    else()
        add_library(${LIB_NAME} SHARED IMPORTED)
        set_target_properties(${LIB_NAME}
                PROPERTIES IMPORTED_LOCATION "${ARG_SHARED_LIB}")
        message("Added shared library dependency ${LIB_NAME}: ${ARG_SHARED_LIB}")
    endif()

    if(ARG_DEPS)
        set_target_properties(${LIB_NAME}
                PROPERTIES IMPORTED_LINK_INTERFACE_LIBRARIES "${ARG_DEPS}")
    endif()

    # Set up an "exported variant" for this thirdparty library (see "Visibility"
    # above). It's the same as the real target, just with an "_exported" suffix.
    # We prefer the static archive if it exists (as it's akin to an "internal"
    # library), but we'll settle for the shared object if we must.
    #
    # A shared object exported variant will force any "leaf" library that
    # transitively depends on it to also depend on it at runtime; this is
    # desirable for some libraries (e.g. cyrus_sasl).
    set(LIB_NAME_EXPORTED "${LIB_NAME}_exported")
    if(ARG_STATIC_LIB)
        add_library(${LIB_NAME_EXPORTED} STATIC IMPORTED)
        set_target_properties(${LIB_NAME_EXPORTED}
                PROPERTIES IMPORTED_LOCATION "${ARG_STATIC_LIB}")
    else()
        add_library(${LIB_NAME_EXPORTED} SHARED IMPORTED)
        set_target_properties(${LIB_NAME_EXPORTED}
                PROPERTIES IMPORTED_LOCATION "${ARG_SHARED_LIB}")
    endif()
    if(ARG_DEPS)
        foreach(DEP ${ARG_DEPS})
            list(APPEND EXPORTED_DEPS "${DEP}_exported")
        endforeach()
        set_target_properties(${LIB_NAME_EXPORTED}
                PROPERTIES IMPORTED_LINK_INTERFACE_LIBRARIES "${EXPORTED_DEPS}")
    endif()
endfunction()

# Look in thirdparty prefix paths before anywhere else for system dependencies.
set(CMAKE_PREFIX_PATH ${THIRDPARTY_INSTALL_DIR})

## OpenSSL
##
## Version 1.0.0 or higher is required because we are using the following
## features introduced started OpenSSL 1.0.0:
##   * The new breed of functions to work with the X509_EXTENSION stack
##   * automatic usage of &errno as a safe per-thread identifier
##
## If having multiple OpenSSL libraries installed on the system,
## use the OPENSSL_ROOT_DIR cmake flag to specify where to look for the proper
## version of the OpenSSL framework/library, e.g.
##
##   cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl ...
##
find_package(OpenSSL 1.0.0 REQUIRED)
include_directories(SYSTEM ${OPENSSL_INCLUDE_DIR})
ADD_THIRDPARTY_LIB(openssl_ssl
        SHARED_LIB "${OPENSSL_SSL_LIBRARY}")
ADD_THIRDPARTY_LIB(openssl_crypto
        SHARED_LIB "${OPENSSL_CRYPTO_LIBRARY}")



## rocksdb
find_package(Rocksdb REQUIRED)
include_directories(SYSTEM ${ROCKSDB_INCLUDE_DIR})
ADD_THIRDPARTY_LIB(rocksdb
        STATIC_LIB "${ROCKSDB_STATIC_LIB}"
        SHARED_LIB "${ROCKSDB_SHARED_LIB}")

############################################################
# Subdirectories
############################################################

add_subdirectory(src/saltfish/server)