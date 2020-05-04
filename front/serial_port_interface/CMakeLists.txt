add_library(serial_port_interface STATIC
        src/serial_port_interface.cpp)
target_include_directories(serial_port_interface PUBLIC src)
target_link_libraries(serial_port_interface ${QT_LIBS} serial_loop)
