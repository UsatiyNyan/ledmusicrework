//
// Created by kira on 29.04.2020.
//
#include "audio_tf_loop.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <atomic>

using namespace std::chrono_literals;

int main() {
    loop::LockFreeContainer container(1024);
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
    loop::AudioTfLoop audio_tf_loop(container,
        pa::DeviceList().get_sources()[0],
        parameters, 1024);
    audio_tf_loop.run();
    clr::RGB &rgb = container.get_rgb();
    std::vector<float> &fft = container.get_fft();
    std::atomic<bool> run = true;
    std::thread timer([&run](){std::this_thread::sleep_for(24s); run = false;});
    size_t ctr = 0;
    while (run) {
        ++ctr;
        std::cout << static_cast<int>(rgb.r) << " | "
                  << static_cast<int>(rgb.g) << " | "
                  << static_cast<int>(rgb.b) << std::endl;
    }
    timer.join();
    std::cout << ctr;
    return 0;
}
