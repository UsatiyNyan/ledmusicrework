#include "bass_adapter.h"

#include "bass_exception.h"

namespace ledplayer {
namespace bass {
OutputAdapter::OutputAdapter(int device, unsigned freq)
    : _freq(freq) {
    if (!BASS_Init(device, _freq, 0, nullptr, nullptr)) {
        throw Exception("BASS_Init");
    }
}

OutputAdapter::~OutputAdapter() {
    if (!BASS_Free()) {
        throw Exception{"BASS_Free"};
    }
}

std::vector<DeviceInfo> OutputAdapter::devices_info() {
    std::vector<DeviceInfo> devices_info{};
    BASS_DEVICEINFO device_info{};
    for (int d = 1; BASS_GetDeviceInfo(d, &device_info); ++d) {
        devices_info.emplace_back(d, device_info);
    }
    return devices_info;
}

DeviceInfo OutputAdapter::device_info(int device_id) {
    BASS_DEVICEINFO device_info{};
    if (!BASS_GetDeviceInfo(device_id, &device_info)) {
        throw Exception{"BASS_GetDeviceInfo: wrong device"};
    }
    return {device_id, device_info};
}

DeviceInfo OutputAdapter::current_device() const {
    return device_info(BASS_GetDevice());
}

Stream OutputAdapter::create_stream(unsigned chans) {
    unsigned handle = BASS_StreamCreate(_freq, chans,
                                        BASS_STREAM_DECODE | BASS_SAMPLE_FLOAT,
                                        STREAMPROC_DUMMY,
                                        nullptr);
    if (!handle) {
        throw bass::Exception{"BASS_StreamCreate"};
    }
    return Stream{handle};
}

InputAdapter::InputAdapter(int device, unsigned freq)
    : _freq(freq) {
    if (!BASS_RecordInit(device)) {
        throw Exception("BASS_RecordInit");
    }
}

InputAdapter::~InputAdapter() {
    if (!BASS_RecordFree()) {
        throw Exception{"BASS_RecordFree"};
    }
}

std::vector<DeviceInfo> InputAdapter::devices_info() {
    std::vector<DeviceInfo> devices_info{};
    BASS_DEVICEINFO device_info{};
    for (int d = 0; BASS_RecordGetDeviceInfo(d, &device_info); ++d) {
        devices_info.emplace_back(d, device_info);
    }
    return devices_info;
}

DeviceInfo InputAdapter::device_info(int device_id) {
    BASS_DEVICEINFO device_info{};
    if (!BASS_RecordGetDeviceInfo(device_id, &device_info)) {
        throw Exception{"BASS_GetDeviceInfo: wrong device"};
    }
    return {device_id, device_info};
}

DeviceInfo InputAdapter::current_device() const {
    return device_info(BASS_RecordGetDevice());
}

Stream InputAdapter::create_stream(unsigned chans) {
    unsigned handle = BASS_RecordStart(_freq, chans,
                                       BASS_STREAM_DECODE | BASS_SAMPLE_FLOAT,
                                       nullptr,
                                       nullptr);
    if (!handle) {
        throw bass::Exception{"BASS_RecordStart"};
    }
    return Stream{handle};
}
}  // namespace bass
}  // namespace ledplayer
