add_library(gpio STATIC)

target_sources(gpio
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/lgpio.cpp
        )

target_include_directories(gpio
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(gpio
        PRIVATE
            hal
        )