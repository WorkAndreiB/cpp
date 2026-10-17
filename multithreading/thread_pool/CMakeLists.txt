cmake_minimum_required(VERSION 3.22)

project(ThreadPool VERSION 1.0.0 LANGUAGES C CXX)

#set C++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

find_package(Threads REQUIRED)

# Add the thread_safe_queue subdirectory to the build
# This will build the ThreadSafeQueue library and make it available for linking
# Use add_subdirectory because the ThreadSafeQueue library is part of the same project and I want to build it as part of this project  
# I could also use find_package(ThreadSafeQueue REQUIRED) if the library was installed in a standard location
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../thread_safe_queue
    ${CMAKE_CURRENT_BINARY_DIR}/thread_safe_queue
)

add_library(ThreadPoolLib src/ThreadPool.cpp)
target_include_directories("ThreadPoolLib" PUBLIC 
    "include"
    "${CMAKE_BINARY_DIR}/config/include")

target_link_libraries("ThreadPoolLib" PUBLIC Threads::Threads "ThreadSafeQueue")

add_executable("ThreadPool" "main.cpp")

target_link_libraries("ThreadPool" PRIVATE "ThreadPoolLib")
