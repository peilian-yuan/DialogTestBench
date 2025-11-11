#pragma once
#ifdef _DEBUG
#define RAII // Resource Acquisition Is Initialization
#endif
#include <winsock2.h>
#include <string>
#include <functional>
#include <memory>

using DELETE_CALLBACK = std::function<void()>;

std::string to_string(const std::wstring& wstr);

//////////////// smart pointer for COM HANDLE ////////
// Create a custom deleter for HANDLE objects
struct HandleDeleter {
    DELETE_CALLBACK m_pfunc;
    void operator()(HANDLE* handle) const {
        if (*handle != INVALID_HANDLE_VALUE) {
            if (m_pfunc)
                m_pfunc();
            else
                CloseHandle(*handle);
        }
        delete handle;
    }
};

using HandlePtr = std::unique_ptr<HANDLE, HandleDeleter>;
HandlePtr CreateComHandle(const std::wstring& portName, DELETE_CALLBACK pfunc = nullptr);

// RAII for network sockets
class Socket {
    SOCKET m_socket;
public:
    Socket() : m_socket(socket(AF_INET, SOCK_STREAM, 0)) {}
    ~Socket() { if (m_socket != INVALID_SOCKET) closesocket(m_socket); }

    // Prevent copying
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    // Allow moving
    Socket(Socket&& other) noexcept : m_socket(other.m_socket) {
        other.m_socket = INVALID_SOCKET;
    }

    // ... other methods
};

class ComPortBufferManager {
private:
    HANDLE m_hCom;
    COMMTIMEOUTS m_origTimeouts;
    bool m_bReadRemainingData;

public:
    ComPortBufferManager(HANDLE hCom, bool bReadRemainingData = true) 
        : m_hCom(hCom)
        , m_bReadRemainingData(bReadRemainingData)
    {
        GetCommTimeouts(m_hCom, &m_origTimeouts);
        // Clear buffer on creation
        ClearRemainingData(m_bReadRemainingData);
    }

    ~ComPortBufferManager() {
        // Restore original timeouts
        SetCommTimeouts(m_hCom, &m_origTimeouts);
    }

    // Optionally provide manual control
    bool ClearRemainingData(bool readRemainingData);
};

std::string GetVersionFromResource();