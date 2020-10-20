//
// Created by kira on 20.10.2020.
//

#include "bass_device.h"

namespace ledplayer {
namespace bass {
DeviceInfo::DeviceInfo(int id, BASS_DEVICEINFO bass_device_info)
    : _id(id), _device_info(bass_device_info) {}

std::string DeviceInfo::dump(char sep) const {
    std::string dump{};
    dump +=
        "id : " + std::to_string(_id) + sep +
            "name: " + _device_info.name + sep +
            "driver: " + _device_info.driver + sep;
    return dump;
}

int DeviceInfo::id() const {
    return _id;
}

std::string DeviceInfo::name() const {
    return _device_info.name;
}

std::string DeviceInfo::driver() const {
    return _device_info.driver;
}
}  // namespace bass
}  // namespace ledplayer
