cmake_minimum_required(VERSION 3.22)

project(SumSolutions VERSION 1.0.0 LANGUAGES C CXX)

#set C++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable("SumExec" "main.cpp")
