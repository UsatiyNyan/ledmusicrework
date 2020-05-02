add_library(serial STATIC
        src/serial.cpp
        )
target_include_directories(serial PUBLIC include)
target_link_libraries(serial PUBLIC file_descriptor base_exception)
