add_library(job_thread STATIC
        src/job_thread.cpp
        )
target_include_directories(job_thread PUBLIC include)
target_link_libraries(job_thread PUBLIC Threads::Threads)
