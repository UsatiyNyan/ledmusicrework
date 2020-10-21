//
// Created by kira on 20.10.2020.
//

#include "bass_stream.h"

#include "bass.h"

#include "bass_exception.h"

namespace {
uint32_t to_bass_data_fft(size_t sample_size) {
    switch (sample_size) {
        case 128: return BASS_DATA_FFT256;
        case 256: return BASS_DATA_FFT512;
        case 512: return BASS_DATA_FFT1024;
        case 1024: return BASS_DATA_FFT2048;
        case 2048: return BASS_DATA_FFT4096;
        case 4096: return BASS_DATA_FFT8192;
        case 8192: return BASS_DATA_FFT16384;
        case 16384: return BASS_DATA_FFT32768;
        default: throw ledplayer::bass::Exception("incorrect sample size");
    }
}
}
namespace ledplayer {
namespace bass {
Stream::Stream(uint32_t handle) : _handle(handle), _fft_data_flag(0) {}

std::vector<float> Stream::fft_data() const {  // TODO: COPY HERE
    std::lock_guard lock{_capture_mutex};
    return {_capture_buf.begin(), _capture_buf.end()};
}

void Stream::update_fft_data(size_t sample_size) {
    if (_capture_buf.size() != sample_size) {
        _fft_data_flag = to_bass_data_fft(sample_size);
        _capture_buf.resize(sample_size);
    }

    while (true) {  // wait for data to be available
        int available = BASS_ChannelGetData(_handle, nullptr, BASS_DATA_AVAILABLE);
        if (available == -1) {
            throw bass::Exception{"BASS_ChannelGetData"};
        } else if (available > 0) {
            break;
        }
    }

    {
        std::lock_guard lock{_capture_mutex};
        if (BASS_ChannelGetData(_handle, _capture_buf.data(), _fft_data_flag) == -1) {
            throw Exception("BASS_ChannelGetData");
        }
    }
}
}  // namespace bass
}  // namespace ledplayer
