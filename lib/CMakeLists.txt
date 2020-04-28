add_subdirectory(base_exception)
add_subdirectory(pulse_adapter)
add_subdirectory(sample)
add_subdirectory(bass_adapter)

set(LIBS pulse_adapter base_exception bass_adapter PARENT_SCOPE)
