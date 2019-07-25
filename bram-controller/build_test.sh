#!/usr/bin/env bash
REMOVE=0
#cmake -D BUILD_TEST=OFF ./
cmake -D CMAKE_C_COMPILER=aarch64-linux-gnu-gcc -D CMAKE_CXX_COMPILER=aarch64-linux-gnu-g++ -D BUILD_TEST=OFF ./
make

if [[ ${REMOVE} -eq 1 ]]
then
    rm -rf cmake_install.cmake CMakeCache.txt Makefile CTestTestfile.cmake CMakeFiles
    cd main
    rm -rf cmake_install.cmake CMakeCache.txt Makefile CTestTestfile.cmake CMakeFiles
    cd ../
    cd test
    rm -rf cmake_install.cmake CMakeCache.txt Makefile CTestTestfile.cmake CMakeFiles
    cd ../
    cd performance
    rm -rf cmake_install.cmake CMakeCache.txt Makefile CTestTestfile.cmake CMakeFiles
    cd ../
fi

scp performance/performance_test performance/test-configuration.cfg root@172.168.1.201:./