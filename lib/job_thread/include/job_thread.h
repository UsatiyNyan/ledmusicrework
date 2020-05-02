//
// Created by kira on 01.05.2020.
//

#ifndef LED_PLAYER_LIB_JOB_THREAD_INCLUDE_JOB_THREAD_H_
#define LED_PLAYER_LIB_JOB_THREAD_INCLUDE_JOB_THREAD_H_

#include <atomic>
#include <thread>

namespace executor {
class JobThread {
 public:
    virtual ~JobThread();
    void run();
    void stop();
 private:
    virtual void job() = 0;

    std::thread _job_thread;
    std::atomic<bool> _run = true;
};
}  // namespace executor

#endif //LED_PLAYER_LIB_JOB_THREAD_INCLUDE_JOB_THREAD_H_
