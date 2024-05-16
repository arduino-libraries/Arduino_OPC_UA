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
cp "$SCRIPT_DIR/Toolchain-gcc-arm-embedded.cmake" .

echo "Build static library libopen62541.a"
mkdir build && cd build
cmake -DCMAKE_C_COMPILER=arm-none-eabi-gcc \
      -DCMAKE_SYSTEM_PROCESSOR=cortex-m7 \
      -DCMAKE_TOOLCHAIN_FILE=../Toolchain-gcc-arm-embedded.cmake\
      -DUA_MULTITHREADING=0 \
      -DUA_ARCHITECTURE=none \
      -DUA_NAMESPACE_ZERO=MINIMAL \
      -DUA_ENABLE_SUBSCRIPTIONS_EVENTS=OFF \
      -DUA_ENABLE_AMALGAMATION=ON \
      -DUA_ENABLE_MALLOC_SINGLETON=ON \
      -DCMAKE_BUILD_TYPE=Release \
      ..
make -j8

echo "Copy precompiled library to Arduino library"
cp bin/libopen62541.a "$LIB_DIR"

echo "Copy amalgated header to Arduino library"
cp open62541.h "$SRC_DIR"
