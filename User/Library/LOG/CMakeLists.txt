add_library(log STATIC)

target_sources(log
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/llog.cpp
        )

target_include_directories(log
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(log
        PRIVATE
            hal
        )