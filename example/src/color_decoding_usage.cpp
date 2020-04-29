//
// Created by kira on 29.04.2020.
//
#include "color.h"
#include "list_devices.h"
#include "bass_adapter.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <fft_stream.h>

using namespace std::chrono_literals;

int main() {
    constexpr size_t size = 1024;
    bass::FFTStream adapter(pa::DeviceList().get_sources().at(0).name, 44100, 2, size);
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
    std::vector<float> float_vector(size);
    size_t ctr = 0;
    std::atomic<bool> run = true;
    std::thread await([&run](){std::this_thread::sleep_for(1s); run = false; return 0;});
    while (run) {
        ++ctr;
        adapter.dispatch_audio_sample(float_vector);
        clr::RGB rgb = color.compute_rgb(float_vector);
        std::cout << static_cast<int>(rgb.r) << " | "
                  << static_cast<int>(rgb.g) << " | "
                  << static_cast<int>(rgb.b) << std::endl;
    }
    await.join();
    std::cout << ctr;
    return 0;
}

