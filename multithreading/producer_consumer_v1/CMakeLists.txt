cmake_minimum_required(VERSION 3.22)

project(ProducerConsumerV1 VERSION 1.0.0 LANGUAGES C CXX)

#set C++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

find_package(Threads REQUIRED)

add_executable("ProducerConsumerV1" "main.cpp")

target_link_libraries("ProducerConsumerV1" PRIVATE Threads::Threads)
