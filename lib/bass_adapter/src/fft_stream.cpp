//
// Created by kira on 29.04.2020.
//

#include "fft_stream.h"
#include "bass_exception.h"

namespace bass {
FFTStream::FFTStream(const std::string &device, uint32_t freq, uint8_t chans, size_t bufsize)
    : _capture_stream(device, freq, chans, bufsize),
      _fft_buffer(bufsize, 0) {
    if (!BASS_Init(0, freq, BASS_DEVICE_LOOPBACK, nullptr, nullptr)) {
        throw BassException("BASS_Init");
    }
    _hstream = BASS_StreamCreate(freq, chans, BASS_STREAM_DECODE | BASS_SAMPLE_FLOAT, STREAMPROC_PUSH, nullptr);
    if (!_hstream) {
        throw BassException("BASS_StreamCreate");
    }
    _fft_stream = std::move(std::thread([this](){
      while (this->_running) {
          this->_capture_stream.get_sample(this->_fft_buffer);
          if (BASS_StreamPutData(_hstream, this->_fft_buffer.data(), this->_fft_buffer.size()) == -1) {
              throw BassException("BASS_StreamPutData");
          }
          if (BASS_ChannelGetData(_hstream, this->_fft_buffer.data(), to_bass_data_fft(this->_fft_buffer.size())) == -1) {
              throw BassException("BASS_ChannelGetData");
          }
      }
    }));
}
FFTStream::~FFTStream() {
    _fft_stream.join();
    BASS_Free();
}
void FFTStream::dispatch_audio_sample(std::vector<float> &buf) {
    if (_fft_buffer.size() != buf.size()) {
        throw BassException("wrong buffer size in FFTStream");
    }
    std::unique_lock<std::mutex> _(this->_mutex);
    buf.swap(_fft_buffer);
}
}  // namespace bass
