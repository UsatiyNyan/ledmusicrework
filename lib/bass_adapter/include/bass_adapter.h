#ifndef LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_ADAPTER_H_
#define LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_ADAPTER_H_

#include "capture.h"

#include "bass.h"

#include <string>
#include <vector>

namespace bass {
class IFFT{
 public:
    virtual void dispatch_audio_sample(std::vector<float> &buf) = 0;
};

class FFT : public IFFT {
 public:
    FFT(const std::string& device, uint32_t freq, uint8_t chans);
    ~FFT();

    void dispatch_audio_sample(std::vector<float> &buf) override;
 private:
    HSTREAM _hstream;
    pa::Capture _capture_device;
    std::vector<float> _capture_buf;
};

uint32_t to_bass_data_fft(size_t sample_size);
}  // namespace bass

#endif