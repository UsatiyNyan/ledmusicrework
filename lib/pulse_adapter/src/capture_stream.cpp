//
// Created by kira on 29.04.2020.
//

#include "capture_stream.h"
#include "base_exception.h"

namespace pa {
CaptureStream::CaptureStream(const std::string &device, uint32_t freq, uint8_t chans, size_t buf_size)
    : _sample_buffer(buf_size, 0),
      _capture(device, freq, chans) {
    _stream = std::thread([this]() {
        while (this->_running) {
            this->_capture.get_sample(this->_sample_buffer);
        }
      });
}
CaptureStream::~CaptureStream() {
    _running = false;
    _stream.join();
}
void CaptureStream::get_sample(std::vector<float> &buf) {
    if (buf.size() != _sample_buffer.size()) {
        throw exception::Exception("wrong buffer size in CaptureStream");
    }
    std::unique_lock<std::mutex> _(this->_mutex);
    buf.swap(_sample_buffer);
}
} // namespace pa
