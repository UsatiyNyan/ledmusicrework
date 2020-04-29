//
// Created by kira on 29.04.2020.
//

#ifndef LED_PLAYER_LIB_COLORS_INCLUDE_RGB_H_
#define LED_PLAYER_LIB_COLORS_INCLUDE_RGB_H_

#include <cstdint>

namespace clr {
struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
struct RGBParameters {
    int half_width;
    int red_peak;
    int green_peak;
    int blue_peak;
    float red_imp;
    float green_imp;
    float blue_imp;
    float filter;
    float sensitivity;
    bool tweak_by_min;
};
}  // namespace colors

#endif //LED_PLAYER_LIB_COLORS_INCLUDE_RGB_H_
