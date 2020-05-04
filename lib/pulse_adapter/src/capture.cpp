//
// Created by kira on 10.11.2019.
//

#include "capture.h"
#include "base_exception.h"

#include <pulse/simple.h>
#include <pulse/error.h>
#include <endian.h>

using exception::Exception;

namespace pa {
Capture::Capture(const std::string &device, uint32_t freq, uint8_t chans) {
    if (BYTE_ORDER == LITTLE_ENDIAN) {
        _sample_spec = {
            .format = PA_SAMPLE_FLOAT32LE,
            .rate = freq,
            .channels = chans};
    } else {
        _sample_spec = {
            .format = PA_SAMPLE_FLOAT32BE,
            .rate = freq,
            .channels = chans};
    }

    int error = 0;
    _simple = pa_simple_new(nullptr, "player_usage", PA_STREAM_RECORD,
                            device.c_str(), "record", &_sample_spec,
                            nullptr, nullptr, &error);
    if (error) {
        throw Exception("pa_simple_new: " + std::string(pa_strerror(error)));
    }
}

Capture::~Capture() {
    pa_simple_free(_simple);
}

void Capture::get_sample(std::vector<float> &buf) {
    int error = 0;
    if (pa_simple_read(_simple, buf.data(), buf.size() * sizeof(float), &error) < 0) {
        throw Exception("pa_simple_read: " + std::string(pa_strerror(error)));
    }
}
}  // namespace pa
