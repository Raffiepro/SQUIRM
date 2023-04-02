#!/bin/bash
cd ..
# rm -R build
mkdir build
cd build
cmake ../
cmake --build .
cd ..
cd build

mkdir That
cp src/that/That That/

mkdir That/libs
cp src/base/libbase.so That/libs