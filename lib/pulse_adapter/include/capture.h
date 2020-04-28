//
// Created by kira on 12.11.2019.
//

#ifndef LED_PLAYER_LIB_PULSE_ADAPTER_INCLUDE_CAPTURE_H_
#define LED_PLAYER_LIB_PULSE_ADAPTER_INCLUDE_CAPTURE_H_

#include <pulse/simple.h>
#include <string>
#include <vector>


namespace pa {
class Capture {
 public:
    explicit Capture(const std::string& device, uint32_t freq, uint8_t chans);
    ~Capture();
    void get_sample(std::vector<float> &buf);

 private:
    pa_sample_spec _sample_spec{};
    pa_simple *_simple = nullptr;
};
} // namespace pa

#endif //LED_PLAYER_LIB_PULSE_ADAPTER_INCLUDE_CAPTURE_H_
