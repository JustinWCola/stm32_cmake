cmake_minimum_required(VERSION 3.25)

project(hello_cmake)

set(CMAKE_CXX_STANDARD 17)

#add_executable(hello_cmake main.cpp)
add_executable(hello_cmake)

target_sources(hello_cmake
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

add_subdirectory(static_lib)

target_link_libraries(hello_cmake
        PRIVATE
            static_lib
        )