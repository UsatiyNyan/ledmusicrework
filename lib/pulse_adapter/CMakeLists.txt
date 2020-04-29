## pulseaudio lib
find_path(PULSEAUDIO_INCLUDE_DIR NAMES pulse/pulseaudio.h)
find_library(PULSEAUDIO_LIBRARY NAMES pulse)

## pulseaudio device parsing and capture
add_library(pulse_adapter STATIC
        src/list_devices.cpp
        src/capture.cpp
        src/capture_stream.cpp)
target_include_directories(pulse_adapter PUBLIC include)
target_link_libraries(pulse_adapter PUBLIC base_exception pulse-simple pulse)
