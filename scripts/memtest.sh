#!/bin/bash
./build.sh
valgrind --leak-check=full ./Wyrm -a test.wyrm