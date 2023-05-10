@echo off
cd ..
rem rm -R build
mkdir build
cd build
cmake -G "MinGW Makefiles" ../
cmake --build .
cd ..
cd build

mkdir Wyrm
cp src/wyrm/Wyrm.exe Wyrm/

cd Wyrm
mkdir libs
cd ..

cp src/base/libbase.dll Wyrm/libs
cp src/amph/libamph.dll Wyrm/libs
rem cp src/test/libtest.so Wyrm/libs

cd ..
cd scripts