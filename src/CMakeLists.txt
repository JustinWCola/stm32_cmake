#add_executable(hello_cmake main.cpp)
add_executable(hello_cmake)

target_sources(hello_cmake
        PRIVATE
            main.cpp
        )

add_subdirectory(static_lib)
add_subdirectory(dynamic_lib)

target_link_libraries(hello_cmake
        PRIVATE
            static_lib
            dynamic_lib
        )