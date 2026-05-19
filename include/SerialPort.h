#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <string>

class SerialPort {
public:
    SerialPort(const std::string& portName, unsigned baudRate = 115200);
    ~SerialPort();

    SerialPort(const SerialPort&) = delete;
    SerialPort& operator=(const SerialPort&) = delete;

    bool isOpen() const;
    bool readLine(std::string& line);

private:
    void* handle_;
    std::string partialLine_;
};

#endif
