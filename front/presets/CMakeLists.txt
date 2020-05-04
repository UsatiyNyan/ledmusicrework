add_library(presets STATIC
        src/savenewdial.cpp
        src/savenewdial.ui
        src/presets.cpp
        src/presets.ui
        )
target_include_directories(presets PUBLIC src)
target_link_libraries(presets ${QT_LIBS} colors geometry)
