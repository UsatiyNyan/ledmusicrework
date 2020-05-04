//
// Created by kira on 29.04.2020.
//

#include "audio_tf_loop.h"

namespace loop {
AudioTfLoop::AudioTfLoop(LockFreeContainer &container,
                         const pa::Device &device, size_t buf_size)
    : _container(container),
      _adapter(device.name, 44100, 2),
      _buf_size(buf_size) {
}
void AudioTfLoop::job() {
    _adapter.dispatch_audio_sample(_container._tmp_fft);
    _container._tmp_rgb = _color.compute_rgb(_container._tmp_fft);
    {
        std::unique_lock _(_mutex);
        _container._rgb = _container._tmp_rgb;
        _container._fft = _container._tmp_fft;
    }
}
void AudioTfLoop::set_params(const clr::RGBParameters &prms) {
    _color.set_params(prms);
}
}  // namespace loop
