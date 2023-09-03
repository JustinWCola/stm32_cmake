add_library(rgb STATIC)

target_sources(rgb
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/lrgb.cpp
        )

target_include_directories(rgb
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(rgb
        PRIVATE
            hal
        )