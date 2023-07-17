add_library(static_lib STATIC)

target_sources(static_lib
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/static_lib.cpp
        )

target_include_directories(static_lib
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )