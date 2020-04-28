//
// Created by kira on 11.11.2019.
//
#include "list_devices.h"

#include <iostream>


int main(int argc, char *argv[]) {
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

    return 0;
}
