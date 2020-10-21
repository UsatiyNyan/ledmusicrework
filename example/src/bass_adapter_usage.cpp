//
// Created by kira on 20.10.2020.
//

#include "bass_adapter.h"
#include "bass_exception.h"
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace ledplayer;

int main() {
    std::vector<bass::DeviceInfo> input_devices = bass::InputAdapter::devices_info();

    bass::InputAdapter adapter{};
    std::cout << "current device:\n" << adapter.current_device().dump() << '\n';

    auto stream = adapter.create_stream(bass::Chans::MONO);

    while (true) {
        stream.update_fft_data(/* TODO make it variable through frontend */);
        auto data = stream.fft_data();
        std::cout << "mean: " << std::accumulate(data.begin(), data.end(), 0.f) / data.size()
                  << '\n';
    }
    return 0;
}
