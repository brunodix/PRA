cmake_minimum_required(VERSION 2.8.4)
project(PRA-T03)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp doublelist.h pseudo_name_generator.cpp pseudo_number_generator.cpp student.cpp student_factory.h student_generator.h timer.h)
add_executable(PRA-T03 ${SOURCE_FILES} )


file(COPY "${CMAKE_BINARY_DIR/}names.txt" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "${CMAKE_BINARY_DIR/}surnames.txt" DESTINATION ${CMAKE_BINARY_DIR})
