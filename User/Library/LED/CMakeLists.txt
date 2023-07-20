add_library(led)

target_sources(led
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/led.cpp
        )

target_include_directories(led
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )