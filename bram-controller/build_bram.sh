#!/usr/bin/env bash
cmake  -D BUILD_TEST=ON ./
#cmake -D CMAKE_C_COMPILER=aarch64-linux-gnu-gcc -D CMAKE_CXX_COMPILER=aarch64-linux-gnu-g++ -D BUILD_TEST=OFF ./
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