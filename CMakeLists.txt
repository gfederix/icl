cmake_minimum_required (VERSION 2.8)
project(iline)
#set(CMAKE_VERBOSE_MAKEFILE on)
set(BASEPATH "${CMAKE_SOURCE_DIR}")
set(SRCDIR "${CMAKE_SOURCE_DIR}/src")

include_directories("${BASEPATH}")
include_directories("${SRCDIR}")
add_subdirectory(src)
add_subdirectory(example)

