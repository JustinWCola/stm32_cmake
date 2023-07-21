add_library(led STATIC)

target_sources(led
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/lled.cpp
        )

target_include_directories(led
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(led
        PRIVATE
            hal
        )