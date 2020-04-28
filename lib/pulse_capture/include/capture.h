//
// Created by kira on 12.11.2019.
//

#ifndef PLAYER_CAPTURE_H
#define PLAYER_CAPTURE_H

#include <pulse/simple.h>
#include <string>
#include <vector>


namespace pa {
class Capture {
 public:
    explicit Capture(const std::string& device);
    ~Capture();
    void get_sample(std::vector<float> &buf, size_t sample_size);

 private:
    pa_sample_spec _sample_spec{};
    pa_simple *_simple = nullptr;
};
} // namespace pa

#endif //PLAYER_CAPTURE_H
