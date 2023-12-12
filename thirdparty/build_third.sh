#!/bin/bash

# path of third lib
PATH_PREFIX=$(pwd)
INSTALL_PATH=$PATH_PREFIX"/installed"
echo "Third Path:"+$INSTALL_PATH

# step-1: install third dep
echo "Step-1: install some dep"
echo "libssl-dev libgflags-dev libprotobuf-dev libprotoc-dev protobuf-compiler libleveldb-dev libgoogle-glog-dev"
sudo apt-get install -y libssl-dev libgflags-dev libprotobuf-dev libprotoc-dev protobuf-compiler libleveldb-dev libgoogle-glog-dev
echo "Step-1: finished"

# step-2: build brpc
echo "Step-2: build brpc"
mkdir -p brpc/build && cd brpc/build
cmake -DWITH_GLOG=ON -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH ..
make -j16 && make install && cd -
echo "Step-2: finished"

# step-3: build braft
echo "Step-3: build braft"
mkdir -p braft/build && cd braft/build
BRPC_INCLUDE_PATH=$INSTALL_PATH/include
BRPC_LIB=$INSTALL_PATH/lib/libbrpc.a
echo "BRPC_INCLUDE_PATH:"$BRPC_INCLUDE_PATH
echo "BRPC_LIB:"$BRPC_LIB
cmake -DBRPC_INCLUDE_PATH=$BRPC_INCLUDE_PATH -DBRPC_LIB=$BRPC_LIB -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH/ -DBRPC_WITH_GLOG=ON ..
make -j16 && make install && cd -
echo "Step-3: finished"

# step-4: build rocksdb
echo "Step-4: build rocksdb"
mkdir -p rocksdb/build && cd rocksdb/build
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH/ ..
make -j16 && make install && cd -
echo "Step-4: finished"


