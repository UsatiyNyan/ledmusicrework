//
// Created by kira on 29.04.2020.
//

#ifndef LED_PLAYER_LIB_COLORS_INCLUDE_COLOR_H_
#define LED_PLAYER_LIB_COLORS_INCLUDE_COLOR_H_

#include "rgb.h"
#include <vector>

namespace clr {
class Color {
 public:
    explicit Color(const RGBParameters &parameters);
    void set_params(const RGBParameters &parameters);
    [[nodiscard]] RGB compute_rgb(const std::vector<float> &fft_data) const;
 private:
    RGBParameters _prm;
};
}  // namespace colors

#endif //LED_PLAYER_LIB_COLORS_INCLUDE_COLOR_H_
