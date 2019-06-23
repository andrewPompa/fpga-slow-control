cmake_minimum_required(VERSION 3.3.2)
project(bram_controller_project)

option(BUILD_BAR_SUBPROJECT "Build targets from subproject Bar" ON)

enable_testing()

add_subdirectory(main)

if(BUILD_BAR_SUBPROJECT)
    add_subdirectory(test)
endif()