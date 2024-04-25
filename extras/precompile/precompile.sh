#!/bin/bash
set -euo pipefail
IFS=$'\n\t'

SCRIPT_DIR=$(dirname $(readlink -f "$0"))
SRC_DIR="$SCRIPT_DIR/../../src"
LIB_DIR="$SRC_DIR/cortex-m7"

echo "Cleaning up"
cd /tmp
rm -rf open62541

echo "Cloning open62541"
git clone --recursive https://github.com/open62541/open62541 && cd open62541
git checkout v1.4.0

echo "Obtaining CMake toolchain definition for ARM"
wget https://raw.githubusercontent.com/swift-nav/libsbp/master/c/cmake/Toolchain-gcc-arm-embedded.cmake

echo "Build static library libopen62541.a"
mkdir build && cd build
cmake -DCMAKE_C_COMPILER=arm-none-eabi-gcc \
      -DCMAKE_SYSTEM_PROCESSOR=cortex-m7 \
      -DCMAKE_TOOLCHAIN_FILE=../Toolchain-gcc-arm-embedded.cmake\
      -DUA_MULTITHREADING=0 \
      -DUA_ARCHITECTURE=none \
      -DUA_NAMESPACE_ZERO=REDUCED \
      -DUA_ENABLE_AMALGAMATION=ON \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      ..
make -j8

echo "Copy precompiled library to Arduino library"
cp bin/libopen62541.a "$LIB_DIR"

echo "Copy amalgated header to Arduino library"
cp open62541.h "$SRC_DIR"
