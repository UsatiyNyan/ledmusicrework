#ifndef __LIST_DEVICES_LIB_H__
#define __LIST_DEVICES_LIB_H__

#include <pulse/pulseaudio.h>
#include <vector>

namespace pa {
struct Device {
    size_t index;
    char name[256];
    char description[256];
};
bool operator==(const Device &device1, const Device &device2);

using DeviceVector = std::vector<Device>;
using ReadyAndDeviceVector = std::pair<bool, DeviceVector>;

class DeviceList {
 public:
    DeviceList();
    ~DeviceList();
    DeviceVector get_sinks();
    DeviceVector get_sources();

 private:
    pa_mainloop *_mainloop;
    pa_mainloop_api *_mainloop_api;
    pa_context *_context;
    pa_operation *_operation = nullptr;
    bool _ready = false;
};
}  // namespace pa

#endif

