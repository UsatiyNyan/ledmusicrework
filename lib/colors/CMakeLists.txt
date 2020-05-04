add_library(colors STATIC
        src/color_settings.cpp)
target_include_directories(colors PUBLIC include)
target_link_libraries(colors PUBLIC bass_adapter)