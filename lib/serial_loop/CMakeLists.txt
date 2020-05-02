add_library(serial_loop STATIC
        src/serial_loop.cpp
        )
target_include_directories(serial_loop PUBLIC include)
target_link_libraries(serial_loop PUBLIC serial base_exception job_thread colors geometry)
