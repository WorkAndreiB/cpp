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

# set path to where cmake files are located
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
# include cmake module file
include(AddGitSubmodule)

option(COMPILE_EXECUTABLE "Whether to compile executable" ON)

# add submodule
add_git_submmodule(external/json)

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
    target_link_libraries(${EXEC_NAME} PUBLIC 
        ${LIB_NAME}
        nlohmann_json)
else()
    message("W/o exe. compiling")
endif()

