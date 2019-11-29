cmake_minimum_required(VERSION 3.14)
project(libcoll C)

set(CMAKE_C_STANDARD 99)

aux_source_directory(src SOURCE)

add_library(${PROJECT_NAME} ${SOURCE})

add_executable(test ${SOURCE})
