cmake_minimum_required(VERSION 3.22)

project(Constructors VERSION 1.0.0 LANGUAGES C CXX)

#set C++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library("smart_ptr_lib" STATIC "src/point.cpp" 
                                    "src/dependency.cpp")

target_include_directories("smart_ptr_lib" PUBLIC
                                    "include")

add_executable("SmartPtrExec" "src/main.cpp")
target_link_libraries("SmartPtrExec" PUBLIC "smart_ptr_lib")