add_library(colors STATIC
        src/color.cpp)
target_include_directories(colors PUBLIC include)
target_link_libraries(colors PUBLIC bass_adapter)