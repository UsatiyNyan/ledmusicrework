//
// Created by kira on 29.04.2020.
//

#include "audio_tf_loop.h"

//#include <iostream>

namespace loop {
LockFreeContainer::LockFreeContainer(size_t bufsize)
: _fft(bufsize, 0), tmp_fft(bufsize, 0) {}

clr::RGB &LockFreeContainer::get_rgb() {
    return _rgb;
}

std::vector<float> &LockFreeContainer::get_fft() {
    return _fft;
}

AudioTfLoop::AudioTfLoop(LockFreeContainer & container,
    const pa::Device &device, const clr::RGBParameters &prms, size_t buf_size)
    : _adapter(device.name, 44100, 2),
      _color(prms),
      _buf_size(buf_size),
      _container(container) {
}
void AudioTfLoop::run() {
    while (_run) {
//        ++_ctr;
        _adapter.dispatch_audio_sample(_container.tmp_fft);
        _container.tmp_rgb = _color.compute_rgb(_container.tmp_fft);
        {
            std::unique_lock _(_mutex);
            _container._rgb = _container.tmp_rgb;
            _container._fft = _container.tmp_fft;
        }
    }
}
void AudioTfLoop::stop() {
//    std::cerr << _ctr << std::endl;
    _run = false;
}
void AudioTfLoop::set_params(const clr::RGBParameters &prms) {
    _color.set_params(prms);
}

}  // namespace loop
