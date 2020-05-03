add_library(main_window STATIC
        src/main_window.ui
        src/main_window.cpp)
target_include_directories(main_window PUBLIC src)
target_link_libraries(main_window ${QT_LIBS} devices)
