//
// Created by kira on 29.04.2020.
//

#ifndef LED_PLAYER_LIB_AUDIO_TF_LOOP_INCLUDE_AUDIO_TF_LOOP_H_
#define LED_PLAYER_LIB_AUDIO_TF_LOOP_INCLUDE_AUDIO_TF_LOOP_H_

#include <mutex>
#include "bass_adapter.h"
#include "list_devices.h"
#include "color_settings.h"
#include "container.h"
#include "job_thread.h"

namespace loop {
class AudioTfLoop : public executor::JobThread {
 public:
    explicit AudioTfLoop(LockFreeContainer &container,
                         const pa::Device &device, size_t buf_size);
    void set_params(const clr::RGBParameters &prms);
 private:
    void job() override;

    LockFreeContainer &_container;
    bass::Adapter _adapter;
    clr::Color _color;
    size_t _buf_size;
    std::mutex _mutex;
};
}  // namespace loop

#endif //LED_PLAYER_LIB_AUDIO_TF_LOOP_INCLUDE_AUDIO_TF_LOOP_H_
