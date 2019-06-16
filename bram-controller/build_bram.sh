#!/usr/bin/env bash
cmake -D CMAKE_C_COMPILER=arm-linux-gnueabihf-gcc -D CMAKE_CXX_COMPILER=arm-linux-gnueabihf-g++ ./
make
rm cmake_install.cmake CMakeCache.txt Makefile