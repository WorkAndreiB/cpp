cmake_minimum_required(VERSION 3.22)

project(ThreadSafeQueue VERSION 1.0.0 LANGUAGES CXX)

#set C++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(ThreadSafeQueue INTERFACE)

target_link_libraries(ThreadSafeQueue INTERFACE Threads::Threads)
target_compile_features(ThreadSafeQueue INTERFACE cxx_std_17)

target_include_directories(ThreadSafeQueue INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(ThreadSafeQueue::ThreadSafeQueue ALIAS ThreadSafeQueue)