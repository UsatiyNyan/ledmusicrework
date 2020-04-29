//
// Created by kira on 29.04.2020.
//

#ifndef LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_FFT_STREAM_H_
#define LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_FFT_STREAM_H_

#include <vector>

#include "bass_adapter.h"
#include "capture_stream.h"

namespace bass {
class FFTStream : public IFFT {
 public:
    FFTStream(const std::string& device, uint32_t freq, uint8_t chans, size_t bufsize);
    ~FFTStream();

    void dispatch_audio_sample(std::vector<float> &buf) override;

 private:
    HSTREAM _hstream;
    pa::CaptureStream _capture_stream;
    std::vector<float> _fft_buffer;
    bool _running = true;
    std::mutex _mutex;
    std::thread _fft_stream;
};
}  // namespace bass

#endif //LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_FFT_STREAM_H_
