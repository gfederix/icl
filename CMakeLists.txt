cmake_minimum_required (VERSION 2.8)
project(iline)
set(CMAKE_VERBOSE_MAKEFILE off)

add_executable(ireadline main.cpp iline.cpp)
add_executable(util_test util_test.cpp util.cpp)
