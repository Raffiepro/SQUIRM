#!/bin/bash
cd ..
# rm -R build
mkdir build
cd build
cmake ../
cmake --build .
cd ..
cd build

mkdir Wyrm 2> /dev/null
cp src/wyrm/Wyrm Wyrm/

mkdir Wyrm/libs 2> /dev/null
cp src/base/libbase.so Wyrm/libs
# cp src/base/libamph.so Wyrm/libs
# cp src/test/libtest.so Wyrm/libs
