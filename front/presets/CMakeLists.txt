add_library(presets STATIC
        src/new_preset_dialog.cpp
        src/new_preset_dialog.ui
        src/presets.cpp
        src/presets.ui
        )
target_include_directories(presets PUBLIC src)
target_link_libraries(presets ${QT_LIBS} colors geometry)
