#!/bin/bash
cd ..
# rm -R build
mkdir build
cd build
cmake ../
cmake --build .
cd ..
cd build

mkdir That 2> /dev/null
cp src/wyrm/That That/

mkdir That/libs 2> /dev/null
cp src/base/libbase.so That/libs
cp src/test/libtest.so That/libs