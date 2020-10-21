//
// Created by kira on 29.04.2020.
//

#include "color_processor.h"

#include <algorithm>

namespace ledplayer {
namespace clr {
void ColorProcessor::set_params(const RGBParameters &parameters) {
    _prm = parameters;
}

RGB ColorProcessor::compute_rgb(const std::vector<float> &fft_data) {
    float r = 0;
    float g = 0;
    float b = 0;
    for (int i = std::max(0, _prm.peak.red - _prm.half_width);
         i < std::min(static_cast<int>(fft_data.size()), _prm.peak.red + _prm.half_width);
         ++i) {
        if (fft_data[i] > _prm.filter) {
            r += fft_data[i]
                * static_cast<float>(std::abs(_prm.half_width - _prm.peak.red + i))
                * static_cast<float>(i);
        }
    }
    for (int i = std::max(0, _prm.peak.green - _prm.half_width);
         i < std::min(static_cast<int>(fft_data.size()), _prm.peak.green + _prm.half_width);
         ++i) {
        if (fft_data[i] > _prm.filter) {
            g += fft_data[i]
                * static_cast<float>(std::abs(_prm.half_width - _prm.peak.green + i))
                * static_cast<float>(i);
        }
    }
    for (int i = std::max(0, _prm.peak.blue - _prm.half_width);
         i < std::min(static_cast<int>(fft_data.size()), _prm.peak.blue + _prm.half_width);
         ++i) {
        if (fft_data[i] > _prm.filter) {
            b += fft_data[i]
                * static_cast<float>(std::abs(_prm.half_width - _prm.peak.blue + i))
                * static_cast<float>(i);
        }
    }

    if (_prm.tweak_by_min) {
        float min_clr = std::min({r, g, b});
        r -= min_clr;
        g -= min_clr;
        b -= min_clr;
    }

    r = r * _prm.sensitivity * _prm.impact.red / static_cast<float>(fft_data.size() * 2);
    g = g * _prm.sensitivity * _prm.impact.green / static_cast<float>(fft_data.size() * 2);
    b = b * _prm.sensitivity * _prm.impact.blue / static_cast<float>(fft_data.size() * 2);

    r = r > 255 ? 255 : r;
    g = g > 255 ? 255 : g;
    b = b > 255 ? 255 : b;

    return {
        .r = static_cast<unsigned>(r),
        .g = static_cast<unsigned>(g),
        .b = static_cast<unsigned>(b)
    };
}
}  // namespace colors
}  // namespace ledplayer
