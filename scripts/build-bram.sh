#!/usr/bin/env bash
cd ../bram
cmake  -D CMAKE_C_COMPILER=arm-linux-gnueabihf-gcc ./
make
rm cmake_install.cmake CMakeCache.txt Makefile