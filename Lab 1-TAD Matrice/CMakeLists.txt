cmake_minimum_required(VERSION 3.28)
project(Lab_1_TAD_Matrice)

set(CMAKE_CXX_STANDARD 20)

# Add include directories
include_directories("Proiect C++" "Teste")

# Add executable from the main directory
add_executable(Lab_1_TAD_Matrice
        "Proiect C++/App.cpp"
        "Proiect C++/Matrice.cpp"
        "Teste/TestExtins.cpp"
        "Teste/TestScurt.cpp"
        "Proiect C++/LSI.h"
)

# Link the test functions
target_link_libraries(Lab_1_TAD_Matrice)