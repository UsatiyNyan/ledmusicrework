//
// Created by kira on 20.10.2020.
//

#ifndef LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_DEVICE_H_
#define LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_DEVICE_H_

#include "bass.h"

#include <string>

namespace ledplayer {
namespace bass {
class DeviceInfo {
 public:
    DeviceInfo(int id, BASS_DEVICEINFO bass_device_info);

    [[nodiscard]] std::string dump(char sep = '\n') const;

    [[nodiscard]] int id() const;
    [[nodiscard]] std::string name() const;
    [[nodiscard]] std::string driver() const;
    // TODO: FLAGS ...

 private:
    int _id;
    BASS_DEVICEINFO _device_info;
};
}  // namespace bass
}  // namespace ledplayer

#endif //LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_DEVICE_H_
