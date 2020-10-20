//
// Created by kira on 29.04.2020.
//

#ifndef LED_PLAYER_LIB_COLORS_INCLUDE_RGB_H_
#define LED_PLAYER_LIB_COLORS_INCLUDE_RGB_H_

namespace clr {
struct RGB {
    unsigned r;
    unsigned g;
    unsigned b;
};
struct RGBParameters {
    int half_width = 128;
    int red_peak = 0;
    int green_peak = 1024;
    int blue_peak = 512;
    int bpm = 100;
    float red_imp = 1;
    float green_imp = 1;
    float blue_imp = 1;
    float filter = 0;
    float sensitivity = 1;
    bool tweak_by_min = true;
};
}  // namespace colors

#endif //LED_PLAYER_LIB_COLORS_INCLUDE_RGB_H_
