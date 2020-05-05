//
// Created by kira on 02.05.2020.
//
#include "container.h"

namespace loop {
LockFreeContainer::LockFreeContainer(size_t bufsize)
    : _fft(bufsize, 0), _tmp_fft(bufsize, 0) {}

clr::RGB &LockFreeContainer::get_rgb() {
    return _rgb;
}

std::vector<float> &LockFreeContainer::get_fft() {
    return _fft;
}
container::FixedQueue<clr::RGB> &LockFreeContainer::get_rgb_queue() {
    return _rgb_queue;
}
}  // namespace loop


