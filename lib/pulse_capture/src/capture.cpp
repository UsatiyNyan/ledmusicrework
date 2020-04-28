//
// Created by kira on 10.11.2019.
//

#include <pulse/simple.h>
#include <pulse/error.h>
#include <cstdint>
#include <iostream>

#include "capture.h"


pa::Capture::Capture() : isSet(false),
                         ss({.format = PA_SAMPLE_FLOAT32,
                                .rate = 44100,
                                .channels = 2}),
                         simple(NULL) {}

int32_t pa::Capture::set_device(std::string device) {
    int32_t error = 0;
    simple = pa_simple_new(NULL, "player_usage", PA_STREAM_RECORD,
                           device.c_str(), "record", &ss, NULL, NULL, &error);
    if (!error) {
        isSet = true;
    }

    return error;
}

pa::Capture::~Capture() {
    if (simple) {
        pa_simple_free(simple);
    }
}

uint32_t pa::Capture::get_sample(void *buf, size_t sample_size) {
    int32_t error = 0;
    uint32_t pa_read =
        pa_simple_read(simple, buf, sample_size * sizeof(float), &error);

    if (pa_read < 0) {
        std::cout << pa_strerror(error) << std::endl;
    }

    return pa_read;
}
