add_library(color_settings STATIC
        src/color_settings.ui
        src/color_settings.cpp)
target_include_directories(color_settings PUBLIC src)
target_link_libraries(color_settings ${QT_LIBS} colors)
