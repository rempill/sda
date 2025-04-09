# Teste/CMakeLists.txt
set(TEST_FILES TestExtins.cpp TestScurt.cpp)

add_executable(tests ${TEST_FILES})
include_directories(${CMAKE_SOURCE_DIR})
target_link_libraries(tests matrice)