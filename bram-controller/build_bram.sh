#!/usr/bin/env bash
cmake  -D BUILD_BAR_SUBPROJECT=ON ./
#cmake -D CMAKE_C_COMPILER=arm-linux-gnueabihf-gcc -D CMAKE_CXX_COMPILER=arm-linux-gnueabihf-g++
make
rm -rf cmake_install.cmake CMakeCache.txt Makefile CTestTestfile.cmake CMakeFiles
cd main
rm -rf cmake_install.cmake CMakeCache.txt Makefile CTestTestfile.cmake CMakeFiles
cd ../
cd test
rm -rf cmake_install.cmake CMakeCache.txt Makefile CTestTestfile.cmake CMakeFiles
cd ../
#rm cmake_install.cmake CMakeCache.txt Makefile CTestTestfile.cmake &
#cd ../library/ &
#rm cmake_install.cmake CMakeCache.txt Makefile CTestTestfile.cmake &
#cd ../test/ &
#rm cmake_install.cmake CMakeCache.txt Makefile CTestTestfile.cmake