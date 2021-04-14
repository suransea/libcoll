cmake_minimum_required(VERSION 3.14)
project(coll C)

set(CMAKE_C_STANDARD 99)

aux_source_directory(src SOURCE)

include_directories(include)

add_library(${PROJECT_NAME} ${SOURCE})


# TEST
add_subdirectory(test)
