#!/bin/bash
./build.sh

cp script.wyrm Wyrm/
cd Wyrm
./Wyrm
./Wyrm -d -r amph script.wyrm
cd ..
