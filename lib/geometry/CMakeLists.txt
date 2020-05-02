add_library(geometry STATIC
        src/polygon.cpp
        src/circle.cpp
        )
target_include_directories(geometry PUBLIC include)
target_link_libraries(geometry PUBLIC base_exception)
