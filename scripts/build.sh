#!/bin/bash
cd ..
# rm -R build
mkdir build
cd build
cmake ../
cmake --build .
cd ..

cd scripts
rm -R Wyrm
mkdir Wyrm 2> /dev/null
cp ../build/src/wyrm/Wyrm Wyrm/

mkdir Wyrm/libs 2> /dev/null
cp ../build/src/base/libbase.so Wyrm/libs
# cp src/base/libamph.so Wyrm/libs
# cp src/test/libtest.so Wyrm/libs
