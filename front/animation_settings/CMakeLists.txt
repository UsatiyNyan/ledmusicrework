add_library(animation_settings STATIC
        src/animation_settings.cpp
        src/animation_settings.ui
        src/polygon_preview.cpp
        src/polygon_preview.ui)
target_include_directories(animation_settings PUBLIC src)
target_link_libraries(animation_settings ${QT_LIBS} ${LIBS})
