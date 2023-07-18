add_library(dynamic_lib SHARED)

target_sources(dynamic_lib
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/dynamic_lib.cpp
        )

target_include_directories(dynamic_lib
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )