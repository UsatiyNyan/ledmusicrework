//
// Created by kira on 28.04.2020.
//

#ifndef LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_EXCEPTION_H_
#define LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_EXCEPTION_H_

#include <exception>
#include <string>

namespace bass {
class BassException : public std::exception {
 public:
    explicit BassException(std::string es);
    [[nodiscard]] const char *what() const noexcept override;
 private:
    std::string _errstr;
};
}  // namespace bass

#endif //LED_PLAYER_LIB_BASS_ADAPTER_INCLUDE_BASS_EXCEPTION_H_
