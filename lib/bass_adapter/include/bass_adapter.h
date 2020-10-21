#ifndef LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_ADAPTER_H_
#define LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_ADAPTER_H_

#include "bass.h"

#include "bass_device.h"
#include "bass_stream.h"
#include "pulse/pulseaudio.h"

#include <string>
#include <vector>

namespace ledplayer {
namespace bass {
enum Chans : unsigned { MONO = 1, STEREO = 2, QUADRAPHONIC = 4, FIVE_ONE = 6, SEVEN_ONE = 8 };
enum Freqs : unsigned { DEFAULT = 44100 };

class OutputAdapter {
 public:
    OutputAdapter(const OutputAdapter &) = delete;
    OutputAdapter &operator=(const OutputAdapter &) = delete;

    explicit OutputAdapter(int device = -1, unsigned freq = Freqs::DEFAULT);
    ~OutputAdapter();

    static std::vector<DeviceInfo> devices_info();
    static DeviceInfo device_info(int device_id);
    [[nodiscard]] DeviceInfo current_device() const;

    Stream create_stream(unsigned chans = Chans::MONO);

 private:
    unsigned _freq;
};

class InputAdapter {
 public:
    InputAdapter(const InputAdapter &) = delete;
    InputAdapter &operator=(const InputAdapter &) = delete;

    explicit InputAdapter(int device = -1, unsigned freq = Freqs::DEFAULT);
    ~InputAdapter();

    static std::vector<DeviceInfo> devices_info();
    static DeviceInfo device_info(int device_id);
    [[nodiscard]] DeviceInfo current_device() const;

    Stream create_stream(unsigned chans = Chans::MONO);

 private:
    unsigned _freq;
};
}  // namespace bass
}  // namespace ledplayer

#endif