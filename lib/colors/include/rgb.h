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
