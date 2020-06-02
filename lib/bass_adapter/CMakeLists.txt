add_library(bass_exception STATIC
        src/bass_exception.cpp)
target_include_directories(bass_exception PUBLIC include)
target_link_libraries(bass_exception PUBLIC bass)

add_library(bass_adapter STATIC
        src/bass_adapter.cpp
        )
target_include_directories(bass_adapter PUBLIC include)
target_link_libraries(bass_adapter PUBLIC bass_exception base_exception pulse_adapter ${CMAKE_CURRENT_SOURCE_DIR}/include/libbass.so)
