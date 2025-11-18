# 0. Create source and CMakeFile
# 1. mkdir build
# 2. cd build
# 3. cmake .. - Generating build file
# 4. cmake --build .
# 5. ./executable


cmake_minimum_required(VERSION 3.22)

project(HelloWorld VERSION 1.0.0 LANGUAGES C CXX)

#set C++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_NAME "PrintLib")
set(EXEC_NAME "HelloWorldExec")

option(COMPILE_EXECUTABLE "Whether to compile executable" OFF)


add_subdirectory(config)

#first target called PrintLib
add_library(${LIB_NAME} STATIC "src/print.cpp")
target_include_directories(${LIB_NAME} PUBLIC 
    "include"
    "${CMAKE_BINARY_DIR}/config/include")

# compile parts of app bassed on conditions
if (COMPILE_EXECUTABLE)
    #second target called HelloWorld
    add_executable(${EXEC_NAME} "src/main.cpp")

    # link to HelloWorld all needed libraries
    target_link_libraries(${EXEC_NAME} PUBLIC ${LIB_NAME})
else()
    message("W/o exe. compiling")
endif()

