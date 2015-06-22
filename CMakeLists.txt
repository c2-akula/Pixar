cmake_minimum_required(VERSION 3.2)
project(Pixar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES Pixar.cpp Pixar.h Robot.cpp Robot.h)
add_executable(Pixar ${SOURCE_FILES} Pixar.cpp Pixar.h Robot.cpp Robot.h)