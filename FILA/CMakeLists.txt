cmake_minimum_required(VERSION 2.8.4)
project(FILA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp
    queue.h)

add_executable(FILA ${SOURCE_FILES})