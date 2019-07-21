cmake_minimum_required(VERSION 3.3.2)
project(bram_controller_project)

set (CMAKE_CXX_STANDARD 11)

option(BUILD_TEST "Build tests" ON)

enable_testing()

add_subdirectory(main)
add_subdirectory(performance)

set(MEMORY_FILE_LOCATION "/dev/mem")

if(BUILD_TEST)
    set(MEMORY_FILE_LOCATION "test/test_memory_file")
    add_subdirectory(test)
endif()
configure_file(program_settings.h.in program_settings.h @ONLY)
