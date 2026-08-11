cmake_minimum_required(VERSION 3.22)

project(ThreadSafeQueue VERSION 1.0.0 LANGUAGES CXX)

find_package(Threads REQUIRED)

add_library(ThreadSafeQueue STATIC "src/thread_safe_queue.cpp")

target_compile_features(ThreadSafeQueue PUBLIC cxx_std_17)

target_include_directories(ThreadSafeQueue PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(ThreadSafeQueue PUBLIC Threads::Threads)

install(TARGETS ThreadSafeQueue
        EXPORT ThreadSafeQueueTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)

