#include "base_exception.h"
#include "list_devices.h"
#include <algorithm>
#include <cstring>

using exception::Exception;

namespace pa {
static void _state_cb(pa_context *ctx, void *userdata) {
    bool *pa_ready = static_cast<bool *>(userdata);
    auto state = pa_context_get_state(ctx);
    switch (state) {
        case PA_CONTEXT_FAILED:
        case PA_CONTEXT_TERMINATED:
            throw Exception(
                "pa_state failed with code: " + std::to_string(state));
        case PA_CONTEXT_READY:*pa_ready = true;
            break;
        default:break;
    }
}

static void _sinklist_cb(pa_context *, const pa_sink_info *sink_info,
                           int eol, void *userdata) {
    auto ready_and_device_vector = static_cast<ReadyAndDeviceVector *>(userdata);
    bool &ready = ready_and_device_vector->first;
    DeviceVector &device_vector = ready_and_device_vector->second;

    if (eol > 0 or !sink_info) {
        ready = true;
        return;
    }

    Device tmp {};
    tmp.index = sink_info->index;
    strncpy(tmp.name, sink_info->name, 255);
    strncpy(tmp.description, sink_info->description, 255);

    if (std::find(device_vector.cbegin(), device_vector.cend(), tmp) != device_vector.cend()) {
        ready = true;
        return;
    }
    device_vector.push_back(tmp);
}

static void _sourcelist_cb(pa_context *, const pa_source_info *source_info,
                             int eol, void *userdata) {
    auto ready_and_device_vector = static_cast<ReadyAndDeviceVector *>(userdata);
    bool &ready = ready_and_device_vector->first;
    DeviceVector &device_vector = ready_and_device_vector->second;

    if (eol > 0 or !source_info) {
        ready = true;
        return;
    }

    Device tmp {};
    tmp.index = source_info->index;
    strncpy(tmp.name, source_info->name, 255);
    strncpy(tmp.description, source_info->description, 255);

    if (std::find(device_vector.cbegin(), device_vector.cend(), tmp) != device_vector.cend()) {
        ready = true;
        return;
    }
    device_vector.push_back(tmp);
}

DeviceList::DeviceList()
: _mainloop(pa_mainloop_new()),
  _mainloop_api(pa_mainloop_get_api(_mainloop)),
  _context(pa_context_new(_mainloop_api, "device_list")) {
    // This function connects to the pulse server
    if (pa_context_connect(_context, NULL, PA_CONTEXT_NOFLAGS, NULL) < 0) {
        throw Exception("context_connect error");
    }
    pa_context_set_state_callback(_context, _state_cb, &_ready);

    // We can't do anything until PA is ready, so just iterate the mainloop
    while (!_ready) {
        if (pa_mainloop_iterate(_mainloop, 1, NULL) < 0) {
            throw Exception("mainloop_iterate error");
        }
    }
}

DeviceList::~DeviceList() {
    pa_operation_unref(_operation);
    pa_context_unref(_context);
    pa_mainloop_free(_mainloop);
}

DeviceVector &&DeviceList::get_sinks() {
    ReadyAndDeviceVector ready_and_device_vector;
    _operation = pa_context_get_sink_info_list(_context, _sinklist_cb, &ready_and_device_vector);
    while (!ready_and_device_vector.first) {
        if (pa_mainloop_iterate(_mainloop, 1, NULL) < 0) {
            throw Exception("mainloop_iterate error");
        }
    }
    return std::move(ready_and_device_vector.second);
}

DeviceVector &&DeviceList::get_sources() {
    ReadyAndDeviceVector ready_and_device_vector;
    _operation = pa_context_get_source_info_list(_context, _sourcelist_cb, &ready_and_device_vector);
    while (!ready_and_device_vector.first) {
        if (pa_mainloop_iterate(_mainloop, 1, NULL) < 0) {
            throw Exception("mainloop_iterate error");
        }
    }
    return std::move(ready_and_device_vector.second);
}

bool operator==(const Device& device1, const Device& device2) {
    return device1.index == device2.index;
}
}  // namespace pa
