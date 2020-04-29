//
// Created by kira on 29.04.2020.
//

#ifndef LED_PLAYER_LIB_PULSE_ADAPTER_INCLUDE_CAPTURE_STREAM_H_
#define LED_PLAYER_LIB_PULSE_ADAPTER_INCLUDE_CAPTURE_STREAM_H_

#include "capture.h"
#include <mutex>
#include <thread>


namespace pa {
class CaptureStream : public ICapture {
 public:
    explicit CaptureStream(const std::string& device, uint32_t freq, uint8_t chans, size_t buf_size);
    ~CaptureStream();
    void get_sample(std::vector<float> &buf) override;
 private:
    std::vector<float> _sample_buffer;
    Capture _capture;
    bool _running = true;
    std::mutex _mutex;
    std::thread _stream;
};
} // namespace pa

#endif //LED_PLAYER_LIB_PULSE_ADAPTER_INCLUDE_CAPTURE_STREAM_H_
