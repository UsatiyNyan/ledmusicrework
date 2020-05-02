//
// Created by kira on 02.05.2020.
//

#include "serial_loop.h"
#include "base_exception.h"


constexpr size_t baud = 19200;

namespace loop {
SerialLoop::SerialLoop(clr::RGB &rgb, const std::string &serial_port)
    : _rgb(rgb),
      _connection(serial_port, baud) {
}
void SerialLoop::job() {
    switch (_mode) {
        case RGB:
            _rgb_buf.assign({_rgb.r, _rgb.g, _rgb.b});
            make_checksum_and_send(_rgb_buf);
            break;
        case BASIC:
        case CIRCLE:
        case POLYGON:
        case BPM:
        case ROTATION:
        case LENGTH_AND_WIDTH:
            make_checksum_and_send(_settings_buf);
            _mode = RGB;
            break;
        default:throw exception::Exception("wrong mode in SerialLoop");
    }
    char *buf[2];
    _connection.read_exact(buf, 2);
}
void SerialLoop::set_basic() {
    _settings_buf.assign({ BASIC });
    _mode = BASIC;
}
void SerialLoop::set_circle(geometry::Point center) {
    _settings_buf.assign({
        CIRCLE,
        static_cast<uint8_t>(center.x),
        static_cast<uint8_t>(center.y)
        });
    _mode = CIRCLE;
}
void SerialLoop::set_polygon(const std::vector<geometry::Point>& vertices) {
    _settings_buf.assign({ POLYGON });
    for (const auto &vertex: vertices) {
        _settings_buf.push_back(static_cast<uint8_t>(vertex.x));
        _settings_buf.push_back(static_cast<uint8_t>(vertex.y));
    }
    _mode = POLYGON;
}
void SerialLoop::set_bpm(uint16_t bpm) {
    _settings_buf.assign({
        BPM,
        static_cast<uint8_t>(bpm >> 1),
        static_cast<uint8_t>(bpm)
    });
    _mode = BPM;
}
void SerialLoop::set_rotation(uint8_t degree) {
    _settings_buf.assign({ROTATION, degree});
    _mode = ROTATION;
}
void SerialLoop::set_length_and_width(uint16_t length, uint16_t width) {
    _settings_buf.assign({
        LENGTH_AND_WIDTH,
        static_cast<uint8_t>(length >> 1),
        static_cast<uint8_t>(length),
        static_cast<uint8_t>(width >> 1),
        static_cast<uint8_t>(width)
    });
    _mode = LENGTH_AND_WIDTH;
}
void SerialLoop::make_checksum_and_send(std::vector<uint8_t>& message) {
    uint8_t check_sum = 0xFF;
    for (uint8_t byte: message) {
        check_sum ^= byte;
    }
    message.insert(message.begin(), check_sum);
    _connection.write_exact(message.data(), message.size());
}
}  // namespace executor
