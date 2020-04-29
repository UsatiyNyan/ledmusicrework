//
// Created by kira on 29.04.2020.
//

#ifndef LED_PLAYER_LIB_AUDIO_TF_LOOP_INCLUDE_AUDIO_TF_LOOP_H_
#define LED_PLAYER_LIB_AUDIO_TF_LOOP_INCLUDE_AUDIO_TF_LOOP_H_

#include <atomic>
#include <mutex>
#include "bass_adapter.h"
#include "list_devices.h"
#include "color.h"

namespace loop {
class LockFreeContainer {
    friend class AudioTfLoop;
 public:
    explicit LockFreeContainer(size_t bufsize);
    clr::RGB &get_rgb();
    std::vector<float> &get_fft();
 private:
    clr::RGB _rgb{};
    std::vector<float> _fft;
    clr::RGB tmp_rgb{};
    std::vector<float> tmp_fft;
};
class AudioTfLoop {
 public:
    explicit AudioTfLoop(LockFreeContainer & container,
        const pa::Device &device, const clr::RGBParameters &prms, size_t buf_size);
    void run();
    void stop();
    void set_params(const clr::RGBParameters &prms);
 private:
    std::mutex _mutex;
    bass::Adapter _adapter;
    clr::Color _color;
    size_t _buf_size;
    std::atomic<bool> _run = true;
    LockFreeContainer &_container;
//    size_t _ctr{};
};
}  // namespace loop

#endif //LED_PLAYER_LIB_AUDIO_TF_LOOP_INCLUDE_AUDIO_TF_LOOP_H_
