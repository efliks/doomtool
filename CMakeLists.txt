cmake_minimum_required(VERSION 3.13)

project(doomtool)

execute_process(COMMAND git describe --tags --always OUTPUT_VARIABLE GIT_VERSION)
string(STRIP "${GIT_VERSION}" GIT_VERSION)

configure_file("gitver.h.in" "gitver.h" @ONLY)

set(GCC_COVERAGE_COMPILE_FLAGS "-W -Wall -pedantic")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_executable(doomtool.exe doomtool.c)

target_link_libraries(doomtool.exe PUBLIC m)
target_include_directories(doomtool.exe PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(doom.exe doom.c)
