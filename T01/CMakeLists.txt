cmake_minimum_required(VERSION 2.8.4)
project(PRA-T01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp generator.cpp node.cpp)
add_executable(PRA-T01 ${SOURCE_FILES})