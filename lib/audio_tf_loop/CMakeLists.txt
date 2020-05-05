add_library(audio_tf_loop STATIC
        src/audio_tf_loop.cpp
        src/container.cpp
        )
target_include_directories(audio_tf_loop PUBLIC include)
target_link_libraries(audio_tf_loop PUBLIC
        bass_adapter
        colors
        bass_exception
        base_exception
        pulse_adapter
        job_thread
        fixed_queue
        )
