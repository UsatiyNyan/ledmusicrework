//
// Created by kira on 29.04.2020.
//

#include "color.h"

#include <algorithm>
#include <iostream>

namespace clr {
Color::Color(const RGBParameters &parameters) : _prm(parameters) {}

void Color::set_params(const RGBParameters &parameters) {
    _prm = parameters;
}

RGB Color::compute_rgb(const std::vector<float> &fft_data) {
    float r = 0;
    float g = 0;
    float b = 0;
    for (int i = std::max(0, _prm.red_peak - _prm.half_width);
         i < std::min(static_cast<int>(fft_data.size()), _prm.red_peak + _prm.half_width);
         ++i) {
        if (fft_data[i] > _prm.filter) {
            r += fft_data[i]
                * static_cast<float>(std::abs(_prm.half_width - _prm.red_peak + i))
                * static_cast<float>(i);
        }
    }
    for (int i = std::max(0, _prm.green_peak - _prm.half_width);
         i < std::min(static_cast<int>(fft_data.size()), _prm.green_peak + _prm.half_width);
         ++i) {
        if (fft_data[i] > _prm.filter) {
            g += fft_data[i]
                * static_cast<float>(std::abs(_prm.half_width - _prm.green_peak + i))
                * static_cast<float>(i);
        }
    }
    for (int i = std::max(0, _prm.blue_peak - _prm.half_width);
         i < std::min(static_cast<int>(fft_data.size()), _prm.blue_peak + _prm.half_width);
         ++i) {
        if (fft_data[i] > _prm.filter) {
            b += fft_data[i]
                * static_cast<float>(std::abs(_prm.half_width - _prm.blue_peak + i))
                * static_cast<float>(i);
        }
    }

    if (_prm.tweak_by_min) {
        float min_clr = std::min({r, g, b});
        r -= min_clr;
        g -= min_clr;
        b -= min_clr;
    }

    r = r * _prm.sensitivity * _prm.red_imp / static_cast<float>(fft_data.size() * 2);
    g = g * _prm.sensitivity * _prm.green_imp / static_cast<float>(fft_data.size() * 2);
    b = b * _prm.sensitivity * _prm.blue_imp / static_cast<float>(fft_data.size() * 2);

    std::cout << static_cast<int>(r) << " | "
              << static_cast<int>(g) << " | "
              << static_cast<int>(b) << std::endl;

    return {
        .r = static_cast<uint8_t>(static_cast<int>(r) % 256),
        .g = static_cast<uint8_t>(static_cast<int>(g) % 256),
        .b = static_cast<uint8_t>(static_cast<int>(b) % 256)
    };
}
}  // namespace colors
