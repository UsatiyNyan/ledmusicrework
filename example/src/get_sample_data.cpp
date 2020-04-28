//
// Created by kira on 28.04.2020.
//
#include "list_devices.h"
#include "bass_adapter.h"
#include <iostream>
#include <numeric>

int main() {
    pa::DeviceList device_list;
    bass::Adapter adapter(device_list.get_sources().at(0).name, 44100, 2);
    std::vector<float> float_vector(1024);
    while (true) {
        adapter.dispatch_audio_sample(float_vector);
        std::cout << std::accumulate(float_vector.cbegin(), float_vector.cend(), 0.) << std::endl;
    }
    return 0;
}