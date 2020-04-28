#ifndef LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_ADAPTER_H_
#define LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_ADAPTER_H_

#include "capture.h"

#include "bass.h"

#include <string>
#include <vector>

namespace bass {
class Adapter {
 public:
    Adapter(const std::string& device, uint32_t freq, uint8_t chans);
    ~Adapter();

    void dispatch_audio_sample(std::vector<float> &buf);

    Adapter() = delete;
    Adapter(const Adapter &) = delete;
    Adapter &operator=(const Adapter &) = delete;
 private:
    HSTREAM _hstream;
    pa::Capture _capture_device;
    std::vector<float> _capture_buf;
};
}  // namespace bass

#endif