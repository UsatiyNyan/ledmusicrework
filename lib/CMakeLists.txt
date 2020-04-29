find_package(Threads)

add_subdirectory(base_exception)
add_subdirectory(pulse_adapter)
add_subdirectory(sample)
add_subdirectory(bass_adapter)
add_subdirectory(colors)
add_subdirectory(audio_tf_loop)

set(LIBS pulse_adapter base_exception bass_adapter colors audio_tf_loop PARENT_SCOPE)
