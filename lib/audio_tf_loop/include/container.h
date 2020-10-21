//
// Created by kira on 02.05.2020.
//

#ifndef LED_PLAYER_LIB_AUDIO_TF_LOOP_INCLUDE_CONTAINER_H_
#define LED_PLAYER_LIB_AUDIO_TF_LOOP_INCLUDE_CONTAINER_H_

#include "color_processor.h"
#include "fixed_queue.h"
#include <vector>

namespace loop {
class LockFreeContainer {
    friend class AudioTfLoop;

 public:
    explicit LockFreeContainer(size_t bufsize);
    clr::RGB &get_rgb();
    std::vector<float> &get_fft();
    container::FixedQueue<clr::RGB> &get_rgb_queue();
 private:
    container::FixedQueue<clr::RGB> _rgb_queue{128};
    clr::RGB _rgb{};
    std::vector<float> _fft;
    clr::RGB _tmp_rgb{};
    std::vector<float> _tmp_fft;
};
}  // namespace loop

#endif //LED_PLAYER_LIB_AUDIO_TF_LOOP_INCLUDE_CONTAINER_H_
