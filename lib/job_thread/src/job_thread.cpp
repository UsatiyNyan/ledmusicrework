//
// Created by kira on 01.05.2020.
//

#include "job_thread.h"

namespace executor {
JobThread::~JobThread() {
    stop();
    _job_thread.join();
}
void JobThread::run() {
    _job_thread = std::thread([this]() {
      while (_run) {
          job();
      }
    });
}
void JobThread::stop() {
    _run = false;
}
}  // namespace executor