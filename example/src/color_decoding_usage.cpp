//
// Created by kira on 29.04.2020.
//
#include "color_processor.h"
#include "bass_adapter.h"
#include <iostream>

using namespace ledplayer;

int main() {
    clr::RGBParameters parameters{
        128,
        0,
        512,
        1024,
        1,
        1,
        1,
        100,
        0,
        1,
        false
    };

    bass::InputAdapter adapter{};  // PA - works as microphone

    clr::ColorProcessor color_processor{};
    color_processor.set_params(parameters);

    auto stream = adapter.create_stream(bass::Chans::STEREO);

    while (true) {
        stream.update_fft_data();
        clr::RGB rgb = color_processor.compute_rgb(stream.fft_data());
        std::cout << rgb.r << " | "
                  << rgb.g << " | "
                  << rgb.b << std::endl;
    }
    return 0;
}

