#!/bin/bash
set -euo pipefail
IFS=$'\n\t'

cd /tmp

rm -rf open62541
git clone --recursive https://github.com/open62541/open62541 && cd open62541
git checkout v1.4.0

wget https://raw.githubusercontent.com/swift-nav/libsbp/master/c/cmake/Toolchain-gcc-arm-embedded.cmake

mkdir build && cd build

cmake -DCMAKE_C_COMPILER=arm-none-eabi-gcc \
      -DCMAKE_SYSTEM_PROCESSOR=cortex-m7 \
      -DCMAKE_TOOLCHAIN_FILE=../Toolchain-gcc-arm-embedded.cmake\
      -DUA_MULTITHREADING=0 \
      -DUA_ARCHITECTURE=none \
      -DUA_NAMESPACE_ZERO=REDUCED \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      ..

make -j8
