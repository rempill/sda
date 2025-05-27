cmake_minimum_required(VERSION 3.28.3)

# Project name
project(Lab7)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories for headers
include_directories(${CMAKE_SOURCE_DIR})
file(GLOB_RECURSE HEADER_DIRS RELATIVE ${CMAKE_SOURCE_DIR} *.h)
foreach(HEADER_FILE ${HEADER_DIRS})
    get_filename_component(HEADER_DIR ${HEADER_FILE} PATH)
    include_directories(${HEADER_DIR})
endforeach()
# Add source files
add_executable(Lab7
        App.cpp
        AB.cpp
        IteratorAB.cpp
        TestExtins.cpp
        TestScurt.cpp
)