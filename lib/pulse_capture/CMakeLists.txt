## thread support
find_package(Threads)

## pulseaudio lib
find_path(PULSEAUDIO_INCLUDE_DIR NAMES pulse/pulseaudio.h)
find_library(PULSEAUDIO_LIBRARY NAMES pulse)

## pulseaudio device parsing
add_library(pulse_device STATIC src/list_devices.cpp)
target_include_directories(pulse_device PUBLIC include)
target_link_libraries(pulse_device PUBLIC pulse base_exception)

## pulseaudio capture
add_library(pulse_capture STATIC src/capture.cpp)
target_include_directories(pulse_capture PUBLIC include)
target_link_libraries(pulse_capture PUBLIC pulse_device pulse-simple pulse)

