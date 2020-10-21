//
// Created by kira on 20.10.2020.
//

#ifndef LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_STREAM_H_
#define LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_STREAM_H_

#include <vector>
#include <cstdint>
#include <mutex>

namespace ledplayer {
namespace bass {
class Stream {
 public:
    explicit Stream(unsigned handle);
    [[nodiscard]] std::vector<float> fft_data() const;

    void update_fft_data(size_t sample_size = 1024);

 private:
    mutable std::mutex _capture_mutex;
    unsigned _handle;
    std::vector<float> _capture_buf;
    unsigned _fft_data_flag;
};
}  // namespace bass
}  // namespace ledplayer

#endif //LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_STREAM_H_
