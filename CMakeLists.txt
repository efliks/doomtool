cmake_minimum_required(VERSION 3.13)

project(doomtool)

set(GCC_COVERAGE_COMPILE_FLAGS "-W -Wall -pedantic")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_executable(doomtool.exe doomtool.c)
target_link_libraries(doomtool.exe PUBLIC m)

add_executable(doom.exe doom.c)
