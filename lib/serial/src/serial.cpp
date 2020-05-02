#include "serial.h"
#include "base_exception.h"

#include <unistd.h>   // UNIX standard function definitions
#include <fcntl.h>    // File control definitions
#include <termios.h>  // POSIX terminal control definitions

using exception::Exception;

namespace serial {
static uint32_t int_to_baud(int baud) {
    switch (baud) {
        case 4800:return B4800;
        case 9600:return B9600;
#ifdef B14400
            case 14400:return B14400;
#endif
        case 19200:return B19200;
#ifdef B28800
            case 28800:return B28800;
#endif
        case 38400:return B38400;
        case 57600:return B57600;
        case 115200:return B115200;
        default: throw Exception("wrong baud number");
    }
}

// takes the string name of the serial port (e.g. "/dev/tty.usbserial","COM1")
// and a baud rate (bps) and connects to that port at that speed and 8N1.
// opens the port in fully raw mode so you can send binary data.
Connection::Connection(const std::string &serialport, int baud) {
    termios tty{};
    //file_descriptor = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);
    _fd = fd::FileDescriptor(open(serialport.c_str(), O_RDWR | O_NONBLOCK));
    if (_fd.fd() == -1) {
        throw Exception("serialport_init: Unable to open port ");
    }

    //int iflags = TIOCM_DTR;
    //ioctl(file_descriptor, TIOCMBIS, &iflags);     // turn on DTR
    //ioctl(file_descriptor, TIOCMBIC, &iflags);    // turn off DTR

    if (tcgetattr(_fd.fd(), &tty) < 0) {
        throw Exception("serialport_init: Couldn't get term attributes");
    }
    speed_t brate = int_to_baud(baud); // let you override switch below if needed

    cfsetispeed(&tty, brate);
    cfsetospeed(&tty, brate);

    // 8N1
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    // no flow control
    tty.c_cflag &= ~CRTSCTS;

    //toptions.c_cflag &= ~HUPCL; // disable hang-up-on-close to avoid reset

    tty.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    tty.c_oflag &= ~OPOST; // make raw

    // see: http://unixwiz.net/techtips/termios-vmin-vtime.html
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 0;
    //toptions.c_cc[VTIME] = 20;

    tcsetattr(_fd.fd(), TCSANOW, &tty);
    if (tcsetattr(_fd.fd(), TCSAFLUSH, &tty) < 0) {
        throw Exception("init_serialport: Couldn't set term attributes");
    }
}

Connection::Connection(Connection &&other) noexcept {
    this->_fd = std::move(other._fd);
}

size_t Connection::write(const void *data, size_t size) {
    ssize_t written = ::write(_fd.fd(), data, size);
    if (written == -1) {
        throw Exception("write error");
    }
    return written;
}

void Connection::write_exact(const void *data, size_t size) {
    size_t written = 0;
    while (size != written) {
        written += write(static_cast<const char *>(data) + written, size - written);
    }
}

size_t Connection::read(void *data, size_t size) {
    ssize_t read_n = ::read(_fd.fd(), data, size);
    if (read_n == -1) {
        throw Exception("read error");
    }
    return read_n;
}

void Connection::read_exact(void *data, size_t size) {
    size_t read_n = 0;
    while (size != read_n) {
        read_n += read(static_cast<char *>(data) + read_n, size - read_n);
    }
}
void Connection::flush() {
    if (tcflush(_fd.fd(), TCIOFLUSH) == -1) {
        throw Exception("tcflush IO");
    }
}
void Connection::flush_input() {
    if (tcflush(_fd.fd(), TCIFLUSH) == -1) {
        throw Exception("tcflush I");
    }
}
void Connection::flush_output() {
    if (tcflush(_fd.fd(), TCOFLUSH) == -1) {
        throw Exception("tcflush O");
    }
}
} // namespace serial
