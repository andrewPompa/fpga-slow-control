cmake_minimum_required (VERSION 2.6)
project (bram)
include_directories ("${PROJECT_SOURCE_DIR}/bram/")
add_executable(bram bram.c base64.h base64.c arguments_validator.h properties_parser/properties_parser.c)