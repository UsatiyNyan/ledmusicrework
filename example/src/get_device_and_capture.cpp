//
// Created by kira on 28.04.2020.
//
#include "capture.h"
#include "list_devices.h"

#include <iostream>
#include <numeric>


int main() {
    pa::DeviceList device_list;
    for (const auto& device: device_list.get_sources()) {
        std::cout << "=======[ Output Device #" << device.index << "]=======" << std::endl;
        std::cout << "Name: " << device.name << std::endl;
        std::cout << "Description: " << device.description << std::endl;
        std::cout << std::endl;
    }
    for (const auto& device: device_list.get_sinks()) {
        std::cout << "=======[ Input Device #" << device.index << "]=======" << std::endl;
        std::cout << "Name: " << device.name << std::endl;
        std::cout << "Description: " << device.description << std::endl;
        std::cout << std::endl;
    }

    pa::Capture capture(device_list.get_sources().at(0).name, 44100, 2);
    std::vector<float> float_vector(1024);
    while (true) {
        capture.get_sample(float_vector, 1024);
        std::cout << std::accumulate(float_vector.cbegin(), float_vector.cend(), 0.) << std::endl;
    }

    return 0;
}
