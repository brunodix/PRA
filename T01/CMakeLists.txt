cmake_minimum_required(VERSION 2.8.4)
project(PRA-T01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp doublelist.cpp pseudo_name_generator.cpp doublenode.cpp pseudo_number_generator.cpp student.cpp quicksort.h timer.cpp timer.h node.h tree.h)
add_executable(PRA-T01 ${SOURCE_FILES})


file(COPY "${CMAKE_BINARY_DIR/}names.txt" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "${CMAKE_BINARY_DIR/}surnames.txt" DESTINATION ${CMAKE_BINARY_DIR})
