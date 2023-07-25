add_library(usart STATIC)

target_sources(usart
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/lusart.cpp
        )

target_include_directories(usart
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(usart
        PRIVATE
            hal
        )