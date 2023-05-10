@echo off
cd ..
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_MAKE_PROGRAM=make ../
cmake --build . 
cd ..