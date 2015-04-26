cmake_minimum_required(VERSION 3.1)
project(T01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    comparators.cpp
    comparators.h
    doublelist.cpp
    doublelist.h
    doublenode.cpp
    doublenode.h
    main.cpp
    pseudo_name_generator.cpp
    pseudo_name_generator.h
    pseudo_number_generator.cpp
    pseudo_number_generator.h
    quicksort.h
    StackBegin.h
    student.cpp
    student.h
    student_factory.h
    student_status.h
    timer.h)

add_executable(T01 ${SOURCE_FILES})