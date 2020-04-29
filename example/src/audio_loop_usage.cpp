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
    std::thread _loop([&audio_tf_loop](){
        audio_tf_loop.run();
    });
    clr::RGB rgb{};
    std::vector<float> float_vector(1024);
    std::atomic<bool> run = true;
    std::thread timer([&run](){std::this_thread::sleep_for(1s); run = false;});
    size_t ctr = 0;
    while (run) {
        ++ctr;
        container.get_data(rgb, float_vector);
        std::cout << static_cast<int>(rgb.r) << " | "
                  << static_cast<int>(rgb.g) << " | "
                  << static_cast<int>(rgb.b) << std::endl;
    }
    audio_tf_loop.stop();
    _loop.join();
    timer.join();
    std::cout << ctr;
    return 0;
}
