add_library(color STATIC
        src/color.ui
        src/color.cpp)
target_include_directories(color PUBLIC include)
target_link_libraries(color ${QT_LIBS})
