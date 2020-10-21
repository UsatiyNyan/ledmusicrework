//
// Created by kira on 29.04.2020.
//

#ifndef LED_PLAYER_LIB_COLORS_INCLUDE_COLOR_SETTINGS_H_
#define LED_PLAYER_LIB_COLORS_INCLUDE_COLOR_SETTINGS_H_

#include "rgb.h"
#include <vector>

namespace ledplayer {
namespace clr {
class ColorProcessor {
 public:
    ColorProcessor() = default;
    void set_params(const RGBParameters &parameters);
    [[nodiscard]] RGB compute_rgb(const std::vector<float> &fft_data);
 private:
    RGBParameters _prm;
};
}  // namespace colors
}  // namespace ledplayer

#endif //LED_PLAYER_LIB_COLORS_INCLUDE_COLOR_SETTINGS_H_
