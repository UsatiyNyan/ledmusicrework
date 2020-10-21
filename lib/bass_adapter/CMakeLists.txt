add_library(bass_adapter STATIC
        src/bass_device.cpp
        src/bass_adapter.cpp
        src/bass_stream.cpp
        src/bass_exception.cpp
        )
target_include_directories(bass_adapter PUBLIC include)
target_link_libraries(bass_adapter PUBLIC
        ledplayer_exception
        pulse_audio
        ${CMAKE_CURRENT_SOURCE_DIR}/include/libbass.so)
