add_subdirectory(base_exception)
add_subdirectory(pulse_capture)
add_subdirectory(sample)

set(LIBS pulse_capture pulse_device base_exception PARENT_SCOPE)
