#!/bin/bash
cd ..
# rm -R build
mkdir build
cd build
cmake -G "MinGW Makefiles" ../
cmake --build .
cd ..
cd build

mkdir Wyrm 2> /dev/null
cp src/wyrm/Wyrm Wyrm/

mkdir Wyrm/libs 2> /dev/null
cp src/base/libbase.dll Wyrm/libs
cp src/amph/libamph.dll Wyrm/libs
# cp src/test/libtest.so Wyrm/libs
