add_library(devices STATIC
        src/devices.ui
        src/devices.cpp)
target_include_directories(devices PUBLIC src)
target_link_libraries(devices ${QT_LIBS} pulse_adapter)
