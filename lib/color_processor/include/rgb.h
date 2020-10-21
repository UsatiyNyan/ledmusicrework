//
// Created by kira on 29.04.2020.
//

#ifndef LED_PLAYER_LIB_COLORS_INCLUDE_RGB_H_
#define LED_PLAYER_LIB_COLORS_INCLUDE_RGB_H_

namespace ledplayer {
namespace clr {
struct RGB {
    unsigned r;
    unsigned g;
    unsigned b;
};
struct RGBParameters {
    struct Peaks {
        int red = 0;
        int green = 1024;
        int blue = 512;
    };

    struct Impact {
        float red = 1.f;
        float green = 1.f;
        float blue = 1.f;
    };

    int half_width = 128;
    Peaks peak{};
    Impact impact{};
    int bpm = 100;
    float filter = 0;
    float sensitivity = 1;
    bool tweak_by_min = true;
};
}  // namespace clr
}  // namespace ledplayer

#endif //LED_PLAYER_LIB_COLORS_INCLUDE_RGB_H_
