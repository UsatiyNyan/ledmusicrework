//
// Created by kira on 02.05.2020.
//

#include "audio_tf_loop.h"
#include "serial_loop.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <iostream>

constexpr const char *serial_port = "/dev/ttyUSB0";

using namespace std::chrono_literals;

int main() {
    loop::LockFreeContainer container(1024);
    clr::RGBParameters parameters;
    loop::AudioTfLoop audio_tf_loop(container,
                                    pa::DeviceList().get_sources()[0],
                                    1024);
    audio_tf_loop.run();

    clr::RGB &rgb = container.get_rgb();
    std::vector<float> &fft = container.get_fft();

    loop::SerialLoop serial_loop(rgb, serial_port);
    serial_loop.run();

    std::atomic<bool> run = true;
    std::thread timer([&run]() {
        std::this_thread::sleep_for(10s);
        run = false;
    });

//    std::vector<geometry::Point> polygon({{1, 1}, {-1, 1}, {-1, -1}, {1, -1}});
//    serial_loop.set_polygon(polygon);
//    serial_loop.set_bpm(160);
    serial_loop.set_circle({0, 0});
//    serial_loop.set_basic();
//    serial_loop.set_length_and_width(8, 8);

    timer.join();

    return 0;
}