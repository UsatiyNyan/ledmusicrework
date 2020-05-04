add_executable(led_player src/main.cpp)
target_link_libraries(led_player ${LIBS} main_window devices serial_port_interface audio_loop_interface)
