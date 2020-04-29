add_library(colors
        src/color.cpp)
target_include_directories(colors PUBLIC include)
target_link_libraries(colors PUBLIC bass_adapter)