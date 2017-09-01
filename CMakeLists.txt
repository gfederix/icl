cmake_minimum_required (VERSION 2.8)
project(iline)
set(CMAKE_VERBOSE_MAKEFILE on)

add_executable(ireadline main.cpp iline.cpp terminal.cpp)
add_executable(util_test util_test.cpp util.cpp terminal.cpp)
add_executable(codeline_test codeline_test.cpp codeline.cpp terminal.cpp util.cpp)
