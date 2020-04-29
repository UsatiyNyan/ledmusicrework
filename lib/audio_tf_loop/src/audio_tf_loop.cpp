//
// Created by kira on 29.04.2020.
//

#include "audio_tf_loop.h"

//#include <iostream>

namespace loop {
LockFreeContainer::LockFreeContainer(size_t bufsize)
: _rgb(), _fft(bufsize, 0) {
}
void LockFreeContainer::get_data(clr::RGB &rgb, std::vector<float> &fft) {
    std::unique_lock _(_mutex);
    rgb = _rgb;
    fft.assign(_fft.cbegin(), _fft.cend());
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
        _adapter.dispatch_audio_sample(_container._fft);
        _container._rgb = _color.compute_rgb(_container._fft);
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
