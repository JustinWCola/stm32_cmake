add_library(can STATIC)

target_sources(can
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/lcan.cpp
        )

target_include_directories(can
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(can
        PRIVATE
            hal
        )