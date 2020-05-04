add_library(audio_loop_interface STATIC
        src/audio_loop_interface.cpp)
target_include_directories(audio_loop_interface PUBLIC src)
target_link_libraries(audio_loop_interface ${QT_LIBS} audio_tf_loop)
