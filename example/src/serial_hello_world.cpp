//
// Created by kira on 03.05.2020.
//
#include "serial.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

constexpr const char *serial_port = "/dev/ttyUSB0";

int main() {
    serial::Connection connection(serial_port, 19200);
    std::vector<uint8_t> buf{{'h', 'u', 'i'}};

    std::cout << connection.write(buf.data(), 3) << std::endl;
    std::this_thread::sleep_for(10s);
}