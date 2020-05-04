set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 COMPONENTS Widgets Core Gui SerialPort REQUIRED)
set(QT_LIBS
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui
        Qt5::SerialPort
        )

add_subdirectory(devices) #
add_subdirectory(serial_port_interface) #
add_subdirectory(audio_loop_interface) #
add_subdirectory(color_settings)
add_subdirectory(presets)

add_subdirectory(main_window)
