cmake_minimum_required(VERSION 3.28.3)
project(Lab4)

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE HEADER_DIRS RELATIVE ${CMAKE_SOURCE_DIR} *.h)
foreach(HEADER_FILE ${HEADER_DIRS})
    get_filename_component(HEADER_DIR ${HEADER_FILE} PATH)
    include_directories(${HEADER_DIR})
endforeach()
add_executable(Lab4 "Proiect C++/App.cpp"
        "Proiect C++/DO.cpp"
        "Proiect C++/DO.h"
        Teste/TestExtins.cpp
        Teste/TestExtins.h
        Teste/TestScurt.cpp
        Teste/TestScurt.h
        "Proiect C++/Iterator.h"
)
