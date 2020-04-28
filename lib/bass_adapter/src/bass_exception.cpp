//
// Created by kira on 28.04.2020.
//
#include "bass_exception.h"
#include "bass.h"
#include <string>
#include <utility>

namespace bass {
std::string error_to_str() {
    switch (BASS_ErrorGetCode()) {
        case BASS_ERROR_UNKNOWN:return "BASS_ERROR_UNKNOWN";
        case BASS_OK:return "BASS_OK";
        case BASS_ERROR_MEM:return "BASS_ERROR_MEM";
        case BASS_ERROR_FILEOPEN:return "BASS_ERROR_FILEOPEN";
        case BASS_ERROR_DRIVER:return "BASS_ERROR_DRIVER";
        case BASS_ERROR_BUFLOST:return "BASS_ERROR_BUFLOST";
        case BASS_ERROR_HANDLE:return "BASS_ERROR_HANDLE";
        case BASS_ERROR_FORMAT:return "BASS_ERROR_FORMAT";
        case BASS_ERROR_POSITION:return "BASS_ERROR_POSITION";
        case BASS_ERROR_INIT:return "BASS_ERROR_INIT";
        case BASS_ERROR_START:return "BASS_ERROR_START";
        case BASS_ERROR_SSL:return "BASS_ERROR_SSL";
        case BASS_ERROR_ALREADY:return "BASS_ERROR_ALREADY";
        case BASS_ERROR_NOCHAN:return "BASS_ERROR_NOCHAN";
        case BASS_ERROR_ILLTYPE:return "BASS_ERROR_ILLTYPE";
        case BASS_ERROR_ILLPARAM:return "BASS_ERROR_ILLPARAM";
        case BASS_ERROR_NO3D:return "BASS_ERROR_NO3D";
        case BASS_ERROR_NOEAX:return "BASS_ERROR_NOEAX";
        case BASS_ERROR_DEVICE:return "BASS_ERROR_DEVICE";
        case BASS_ERROR_NOPLAY:return "BASS_ERROR_NOPLAY";
        case BASS_ERROR_FREQ:return "BASS_ERROR_FREQ";
        case BASS_ERROR_NOTFILE:return "BASS_ERROR_NOTFILE";
        case BASS_ERROR_NOHW:return "BASS_ERROR_NOHW";
        case BASS_ERROR_EMPTY:return "BASS_ERROR_EMPTY";
        case BASS_ERROR_NONET:return "BASS_ERROR_NONET";
        case BASS_ERROR_CREATE:return "BASS_ERROR_CREATE";
        case BASS_ERROR_NOFX:return "BASS_ERROR_NOFX";
        case BASS_ERROR_NOTAVAIL:return "BASS_ERROR_NOTAVAIL";
        case BASS_ERROR_DECODE:return "BASS_ERROR_DECODE";
        case BASS_ERROR_DX:return "BASS_ERROR_DX";
        case BASS_ERROR_TIMEOUT:return "BASS_ERROR_TIMEOUT";
        case BASS_ERROR_FILEFORM:return "BASS_ERROR_FILEFORM";
        case BASS_ERROR_SPEAKER:return "BASS_ERROR_SPEAKER";
        case BASS_ERROR_VERSION:return "BASS_ERROR_VERSION";
        case BASS_ERROR_CODEC:return "BASS_ERROR_CODEC";
        case BASS_ERROR_ENDED:return "BASS_ERROR_ENDED";
        case BASS_ERROR_BUSY:return "BASS_ERROR_BUSY";
        default:return "error code isn't even unknown, hmmmm....";
    }
}

const char *BassException::what() const noexcept {
    return _errstr.c_str();
}

BassException::BassException(std::string es) {
    _errstr = std::move(es) + "\n" + error_to_str();
}
}  // namespace bass
