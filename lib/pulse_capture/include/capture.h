//
// Created by kira on 12.11.2019.
//

#ifndef PLAYER_CAPTURE_H
#define PLAYER_CAPTURE_H

#include <pulse/simple.h>
#include <pulse/error.h>
#include <cstdint>
#include <string>


namespace pa {
class Capture {
 public:
    Capture();
    ~Capture();
    int32_t set_device(std::string device);
    uint32_t get_sample(void *buf, size_t sample_size);

    bool isSet;
 private:
    pa_sample_spec ss;
    pa_simple *simple;
};
}
#endif //PLAYER_CAPTURE_H
