#include "bass_adapter.h"

#include "bass_exception.h"

namespace bass {
static uint32_t to_bass_data_fft(size_t sample_size) {
    switch (sample_size) {
        case 128: return BASS_DATA_FFT256;
        case 256: return BASS_DATA_FFT512;
        case 512: return BASS_DATA_FFT1024;
        case 1024: return BASS_DATA_FFT2048;
        case 2048: return BASS_DATA_FFT4096;
        case 4096: return BASS_DATA_FFT8192;
        case 8192: return BASS_DATA_FFT16384;
        case 16384: return BASS_DATA_FFT32768;
        default:throw BassException("incorrect sample_size");
    }
}

Adapter::Adapter(const std::string &device, uint32_t freq, uint8_t chans)
    : _capture_device(device, freq, chans),
      _capture_buf(2048, 0) {
    if (!BASS_Init(0, freq, BASS_DEVICE_LOOPBACK, nullptr, nullptr)) {
        throw BassException("BASS_Init");
    }
    _hstream =
        BASS_StreamCreate(freq, chans, BASS_STREAM_DECODE | BASS_SAMPLE_FLOAT, STREAMPROC_PUSH, nullptr);
    if (!_hstream) {
        throw BassException("BASS_StreamCreate");
    }
}

Adapter::~Adapter() {
    BASS_Free();
}

void Adapter::dispatch_audio_sample(std::vector<float> &buf) {
    if (_capture_buf.size() != buf.size()) {
        to_bass_data_fft(buf.size());  // try to get the BASS_DATA_FFT...
        std::vector<float>(buf.size(), 0).swap(_capture_buf);
    }
    _capture_device.get_sample(_capture_buf);
    if (BASS_StreamPutData(_hstream, _capture_buf.data(), _capture_buf.size()) == -1) {
        throw BassException("BASS_StreamPutData");
    }
    if (BASS_ChannelGetData(_hstream, buf.data(), to_bass_data_fft(buf.size())) == -1) {
        throw BassException("BASS_ChannelGetData");
    }

}
}  // namespace bass
