cmake_minimum_required(VERSION 3.12)
project(misc_cpp)

set(CMAKE_CXX_STANDARD 14)
add_executable(solution main.cpp)
add_executable(naive naive.cpp)
add_executable(testgen testgen.cpp)
add_executable(solution_debug main.cpp)
target_compile_definitions(solution_debug PRIVATE DEBUG INPUTFILE="../std.in")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

