add_library(bass_exception
        src/bass_exception.cpp)
target_include_directories(bass_exception PUBLIC include)
target_link_libraries(bass_exception PUBLIC bass)

add_library(bass_adapter
        src/bass_adapter.cpp
        src/fft_stream.cpp
        )
target_include_directories(bass_adapter PUBLIC include)
target_link_libraries(bass_adapter PUBLIC bass_exception base_exception bass pulse_adapter Threads::Threads)
