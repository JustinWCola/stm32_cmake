cmake_minimum_required(VERSION 3.25)

project(hello_cmake)

set(CMAKE_CXX_STANDARD 17)

# add_executable(hello_cmake main.cpp)

# Modern CMake
add_executable(hello_cmake)

target_sources(hello_cmake
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )