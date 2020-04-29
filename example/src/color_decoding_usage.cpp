//
// Created by kira on 29.04.2020.
//
#include "color.h"
#include "list_devices.h"
#include "bass_adapter.h"
#include <iostream>

int main() {
    bass::Adapter adapter(pa::DeviceList().get_sources().at(0).name, 44100, 2);
    clr::RGBParameters parameters {
        128,
        0,
        512,
        1024,
        1,
        1,
        1,
        0,
        1,
        false
    };
    clr::Color color(parameters);
    std::vector<float> float_vector(1024);
    while (true) {
        adapter.dispatch_audio_sample(float_vector);
        clr::RGB rgb = color.compute_rgb(float_vector);
//        std::cout << static_cast<int>(rgb.r) << " | "
//                  << static_cast<int>(rgb.g) << " | "
//                  << static_cast<int>(rgb.b) << std::endl;
    }
    return 0;
}

