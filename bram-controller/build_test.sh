#!/usr/bin/env bash
#cmake  -D BUILD_TEST=ON ./
cmake -D CMAKE_C_COMPILER=aarch64-linux-gnu-gcc -D CMAKE_CXX_COMPILER=aarch64-linux-gnu-g++ -D BUILD_TEST=OFF ./
make
cd main
cd ../
cd test
cd ../
cd performance
cd ../
scp performance/performance_test performance/test-configuration.cfg root@172.168.1.201:./