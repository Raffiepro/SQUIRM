#!/bin/bash
./build.sh

cp script.wyrm Wyrm/
cd Wyrm
./Wyrm -a -d script.wyrm
cd ..
