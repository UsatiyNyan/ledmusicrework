add_subdirectory(base_exception)
add_subdirectory(pulse_adapter)
add_subdirectory(sample)
add_subdirectory(bass_adapter)
add_subdirectory(colors)

set(LIBS pulse_adapter base_exception bass_adapter colors PARENT_SCOPE)
