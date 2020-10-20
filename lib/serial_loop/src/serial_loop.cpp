//
// Created by kira on 02.05.2020.
//

#include "serial_loop.h"
#include "ledplayer_exception.h"
#include <chrono>
//#include <iostream>

using namespace std::chrono_literals;

constexpr size_t baud = 19200;

namespace loop {
SerialLoop::SerialLoop(clr::RGB &rgb, const std::string &serial_port)
    : _rgb(rgb),
      _connection(serial_port, baud) {
}

void SerialLoop::job() {
    switch (_mode) {
        case RGB:parse_rgb();
            break;
        case BASIC:
        case CIRCLE:
        case POLYGON:
        case BPM:
        case ROTATION:
        case LENGTH_AND_WIDTH:make_checksum_and_send(_settings_buf);
            _mode = RGB;
            break;
        default:throw exception::Exception("wrong mode in SerialLoop");
    }
    std::this_thread::sleep_for(10ms);
}

void SerialLoop::parse_rgb() {
    _rgb_buf.assign(
        {RGB,
         static_cast<uint8_t>('0' + _rgb.r / 100),
         static_cast<uint8_t>('0' + _rgb.r / 10 % 10),
         static_cast<uint8_t>('0' + _rgb.r % 10),
         static_cast<uint8_t>('0' + _rgb.g / 100),
         static_cast<uint8_t>('0' + _rgb.g / 10 % 10),
         static_cast<uint8_t>('0' + _rgb.g % 10),
         static_cast<uint8_t>('0' + _rgb.b / 100),
         static_cast<uint8_t>('0' + _rgb.b / 10 % 10),
         static_cast<uint8_t>('0' + _rgb.b % 10)});
    make_checksum_and_send(_rgb_buf);
}

void SerialLoop::set_basic() {
    _settings_buf.assign({BASIC});
    _mode = BASIC;
}

void SerialLoop::set_circle(geometry::Point center) {
    center.x += 500;
    center.y += 500;
    _settings_buf.assign({
                             CIRCLE,
                             static_cast<uint8_t>('0' + static_cast<int>(center.x) / 100),
                             static_cast<uint8_t>('0' + static_cast<int>(center.x) / 10 % 10),
                             static_cast<uint8_t>('0' + static_cast<int>(center.x) % 10),
                             static_cast<uint8_t>('0' + static_cast<int>(center.y) / 100),
                             static_cast<uint8_t>('0' + static_cast<int>(center.y) / 10 % 10),
                             static_cast<uint8_t>('0' + static_cast<int>(center.y) % 10)
                         });
    _mode = CIRCLE;
}

void SerialLoop::set_polygon(const std::vector<geometry::Point> &vertices) {
    _settings_buf.assign({POLYGON});
    for (auto &vertex: std::vector(vertices)) {
        vertex.x += 500;
        vertex.y += 500;
        _settings_buf.push_back(static_cast<uint8_t>('0' + static_cast<int>(vertex.x) / 100));
        _settings_buf.push_back(static_cast<uint8_t>('0' + static_cast<int>(vertex.x) / 10 % 10));
        _settings_buf.push_back(static_cast<uint8_t>('0' + static_cast<int>(vertex.x) % 10));
        _settings_buf.push_back(static_cast<uint8_t>('0' + static_cast<int>(vertex.y) / 100));
        _settings_buf.push_back(static_cast<uint8_t>('0' + static_cast<int>(vertex.y) / 10 % 10));
        _settings_buf.push_back(static_cast<uint8_t>('0' + static_cast<int>(vertex.y) % 10));
    }
    _mode = POLYGON;
}

void SerialLoop::set_bpm(uint16_t bpm) {
    _settings_buf.assign({
                             BPM,
                             static_cast<uint8_t>('0' + bpm / 100),
                             static_cast<uint8_t>('0' + bpm / 10 % 10),
                             static_cast<uint8_t>('0' + bpm % 10)
                         });
    _mode = BPM;
}

void SerialLoop::set_rotation(int16_t degree) {
    degree += 180;
    _settings_buf.assign({
                             ROTATION,
                             static_cast<uint8_t>('0' + degree / 100),
                             static_cast<uint8_t>('0' + degree / 10 % 10),
                             static_cast<uint8_t>('0' + degree % 10)
                         });
    _mode = ROTATION;
}

void SerialLoop::set_length_and_width(uint16_t length, uint16_t width) {
    _settings_buf.assign({
                             LENGTH_AND_WIDTH,
                             static_cast<uint8_t>('0' + length / 100),
                             static_cast<uint8_t>('0' + length / 10 % 10),
                             static_cast<uint8_t>('0' + length % 10),
                             static_cast<uint8_t>('0' + width / 100),
                             static_cast<uint8_t>('0' + width / 10 % 10),
                             static_cast<uint8_t>('0' + width % 10)
                         });
    _mode = LENGTH_AND_WIDTH;
}

void SerialLoop::make_checksum_and_send(std::vector<uint8_t> &message) {
    /* general structure of a message:
     * '<' | checksum | flag | data | '>'
     * */
    uint8_t check_sum = 0xFF;
    for (uint8_t byte: message) {
        check_sum ^= byte;
    }
    message.insert(message.begin(), check_sum);
    message.insert(message.begin(), '<');
    message.push_back('>');
    _connection.write_exact(message.data(), message.size());
}
}  // namespace executor
