//
// Created by kira on 02.05.2020.
//

#ifndef LED_PLAYER_LIB_SERIAL_LOOP_INCLUDE_SERIAL_LOOP_H_
#define LED_PLAYER_LIB_SERIAL_LOOP_INCLUDE_SERIAL_LOOP_H_

#include "job_thread.h"
#include "serial.h"
#include "color_settings.h"
#include "circle.h"
#include "polygon.h"

namespace loop {
enum FLAGS : uint8_t {
    BASIC = 0x00,
    CIRCLE = 0x01,
    POLYGON = 0x02,
    BPM = 0x03,
    ROTATION = 0x04,
    LENGTH_AND_WIDTH = 0x05,
    RGB = 0xFF,
};

class SerialLoop : public executor::JobThread {
 public:
    explicit SerialLoop(clr::RGB &rgb, const std::string &serial_port);
    void parse_rgb();
    void set_basic();
    void set_circle(geometry::Point center);
    void set_polygon(const std::vector<geometry::Point> &vertices);
    void set_bpm(uint16_t bpm);
    void set_rotation(int16_t degree);
    void set_length_and_width(uint16_t length, uint16_t width);
 private:
    void job() override;
    void make_checksum_and_send(std::vector<uint8_t> &message);

    serial::Connection _connection;
    clr::RGB &_rgb;
    std::atomic<uint8_t> _mode = RGB;
    std::vector<uint8_t> _rgb_buf{};
    std::vector<uint8_t> _settings_buf{};
};
}  // namespace executor


#endif //LED_PLAYER_LIB_SERIAL_LOOP_INCLUDE_SERIAL_LOOP_H_
