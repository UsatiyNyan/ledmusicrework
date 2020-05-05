add_library(animation_view STATIC
        src/animation_view.cpp
        src/animation_view.ui)
target_include_directories(animation_view PUBLIC src)
target_link_libraries(animation_view ${QT_LIBS} ${LIBS})
