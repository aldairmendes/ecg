#include "SerialPort.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <iostream>

namespace {

std::string toDevicePath(const std::string& portName) {
    if (portName.rfind("\\\\.\\", 0) == 0) {
        return portName;
    }
    return "\\\\.\\" + portName;
}

}  // namespace

SerialPort::SerialPort(const std::string& portName, unsigned baudRate)
    : handle_(INVALID_HANDLE_VALUE) {
    HANDLE h = CreateFileA(
        toDevicePath(portName).c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr);

    if (h == INVALID_HANDLE_VALUE) {
        std::cerr << "Erro ao abrir porta " << portName << " (codigo " << GetLastError() << ")\n";
        return;
    }

    DCB dcb{};
    dcb.DCBlength = sizeof(DCB);
    if (!GetCommState(h, &dcb)) {
        CloseHandle(h);
        std::cerr << "Erro ao ler configuracao da porta.\n";
        return;
    }

    dcb.BaudRate = baudRate;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    dcb.fDtrControl = DTR_CONTROL_ENABLE;
    dcb.fRtsControl = RTS_CONTROL_ENABLE;

    if (!SetCommState(h, &dcb)) {
        CloseHandle(h);
        std::cerr << "Erro ao configurar porta serial.\n";
        return;
    }

    PurgeComm(h, PURGE_RXCLEAR | PURGE_TXCLEAR);
    EscapeCommFunction(h, SETDTR);

    COMMTIMEOUTS timeouts{};
    timeouts.ReadIntervalTimeout = MAXDWORD;
    timeouts.ReadTotalTimeoutConstant = 100;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    SetCommTimeouts(h, &timeouts);

    handle_ = h;
}

SerialPort::~SerialPort() {
    if (handle_ != INVALID_HANDLE_VALUE) {
        CloseHandle(static_cast<HANDLE>(handle_));
    }
}

bool SerialPort::isOpen() const {
    return handle_ != INVALID_HANDLE_VALUE;
}

bool SerialPort::readLine(std::string& line) {
    line.clear();

    if (!isOpen()) {
        return false;
    }

    HANDLE h = static_cast<HANDLE>(handle_);
    char ch = '\0';
    DWORD bytesRead = 0;

    while (true) {
        if (!partialLine_.empty()) {
            const std::size_t pos = partialLine_.find('\n');
            if (pos != std::string::npos) {
                line = partialLine_.substr(0, pos);
                partialLine_.erase(0, pos + 1);
                while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) {
                    line.pop_back();
                }
                return true;
            }
        }

        if (!ReadFile(h, &ch, 1, &bytesRead, nullptr) || bytesRead == 0) {
            return false;
        }

        partialLine_.push_back(ch);

        const std::size_t pos = partialLine_.find('\n');
        if (pos != std::string::npos) {
            line = partialLine_.substr(0, pos);
            partialLine_.erase(0, pos + 1);
            while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) {
                line.pop_back();
            }
            return true;
        }
    }
}
