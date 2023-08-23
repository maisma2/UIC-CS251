cmake_minimum_required(VERSION 3.25) # or higher if necessary
project(CS251Proj4)
set( CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++" )
set( CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc" )

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


add_executable(CS251Proj4 main.cpp hashmap.cpp hashmap.h util.h bitstream.h)
