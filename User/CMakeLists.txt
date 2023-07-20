target_sources(${PROJECT_NAME}.elf
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/mainpp.cpp
        )

add_subdirectory(Library)
add_subdirectory(Application)

target_link_libraries(${PROJECT_NAME}.elf
        PRIVATE
            led
        )