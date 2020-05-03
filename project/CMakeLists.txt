add_executable(led_player src/main.cpp)
target_link_libraries(led_player ${LIBS} main_window devices)
