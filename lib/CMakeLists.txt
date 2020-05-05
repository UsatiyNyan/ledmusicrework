find_package(Threads)

add_subdirectory(base_exception)
add_subdirectory(pulse_adapter)
add_subdirectory(bass_adapter)
add_subdirectory(colors)
add_subdirectory(job_thread)
add_subdirectory(audio_tf_loop)
add_subdirectory(file_descriptor)
add_subdirectory(serial)
add_subdirectory(geometry)
add_subdirectory(serial_loop)
add_subdirectory(fixed_queue)

set(LIBS
        base_exception
        pulse_adapter
        bass_adapter
        colors
        job_thread
        audio_tf_loop
        file_descriptor
        serial
        geometry
        serial_loop
        fixed_queue
        PARENT_SCOPE)

