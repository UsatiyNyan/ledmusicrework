add_executable(bass_adapter_usage src/bass_adapter_usage.cpp)
target_link_libraries(bass_adapter_usage bass_adapter)

add_executable(color_decoding_usage src/color_decoding_usage.cpp)
target_link_libraries(color_decoding_usage color_processor bass_adapter)

add_executable(audio_loop_usage src/audio_loop_usage.cpp)
target_link_libraries(audio_loop_usage audio_tf_loop)

add_executable(devlist src/devlist.cpp)
target_link_libraries(devlist bass_adapter)

add_executable(spectrum src/spectrum.cpp)
target_link_libraries(spectrum bass_adapter)

add_executable(basic_audio_and_serial_loop src/basic_audio_and_serial_loop.cpp)
target_link_libraries(basic_audio_and_serial_loop ${LIBS})

add_executable(serial_hello_world src/serial_hello_world.cpp)
target_link_libraries(serial_hello_world ${LIBS})

add_executable(devices_front_usage src/devices_front_usage.cpp)
target_link_libraries(devices_front_usage devices)
