#ifndef LED_PLAYER_LIB_SERIAL_INCLUDE_SERIAL_H_
#define LED_PLAYER_LIB_SERIAL_INCLUDE_SERIAL_H_

#include "file_descriptor.h"
#include <string>

namespace serial {
class Connection {
 public:
    Connection(const std::string &serialport, int baud);
    Connection(Connection &&other) noexcept;

    size_t write(const void *data, size_t size);
    void write_exact(const void *data, size_t size);
    size_t read(void *data, size_t size);
    void read_exact(void *data, size_t size);
    void flush();
    void flush_input();
    void flush_output();
 private:
    fd::FileDescriptor _fd;
};
}  // namespace serial
#endif
