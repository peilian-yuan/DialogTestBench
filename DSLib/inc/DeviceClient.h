#pragma once
#include <vector>
#include <string>
#include <mutex>
#include <queue>
#include <functional>

#define MAX_BUFF_LEN 4096
#define QUERY_END "?\x0D"

// types of message
enum class MessageType {
    CONNECT,        // connection
    DISCONNECT,     // disconnection
    BROADCAST,      // broadcast
    PRIVATE,        // private message
    COMMAND         // command
};

// Message structure
struct Message {
    MessageType type;
    std::string sender;
    std::string recipient; // only for private message
    std::string content;
    time_t timestamp;

    Message(MessageType t, const std::string& c)
        : type(t), sender(""), recipient(""), content(""), timestamp(time(nullptr)) {}

    Message(MessageType t, const std::string& s, const std::string& c)
        : type(t), sender(s), content(c), timestamp(time(nullptr)) {}

    Message(MessageType t, const std::string& s, const std::string& r, const std::string& c)
        : type(t), sender(s), recipient(r), content(c), timestamp(time(nullptr)) {}
};

// information of client connection
class ClientConnection
{
public:
    SOCKET socket;
    std::string hostname;
    std::string ip;
    int port;
    std::atomic<bool> active;
    std::queue<std::string> messageQueue;
    std::mutex queueMutex;
    //std::condition_variable cv;

    // delete copying and assigning constructor, don't allow to copying and assigning operations
    ClientConnection(const ClientConnection&) = delete;
    ClientConnection& operator=(const ClientConnection&) = delete;

    // default constructor
    ClientConnection() : socket(INVALID_SOCKET), port(0), active(false) {}

    // constructor for moving copy
    ClientConnection(ClientConnection&& other) noexcept
        : socket(other.socket),
        hostname(std::move(other.hostname)),
        ip(std::move(other.ip)),
        port(other.port),
        active(other.active.load()),
        messageQueue(std::move(other.messageQueue)) {
        other.socket = INVALID_SOCKET;
        other.active = false;
    }

    // assigning operation for moving copy
    ClientConnection& operator=(ClientConnection&& other) noexcept {
        if (this != &other) {
            socket = other.socket;
            hostname = std::move(other.hostname);
            ip = std::move(other.ip);
            port = other.port;
            active = other.active.load();
            messageQueue = std::move(other.messageQueue);

            other.socket = INVALID_SOCKET;
            other.active = false;
        }
        return *this;
    }
};

class DeviceClient
{
    SOCKET serverSocket;
    char m_rcvBuffer[MAX_BUFF_LEN] = { 0 };
    std::thread serverThread;
    std::atomic<bool> running;
    std::function<void(std::string, DeviceClient*)> f_callback;
    std::map<std::string, ClientConnection> m_clients;
    std::mutex clientsMutex;

    void receiveLoop(SOCKET socket);
    bool receive(std::string hostname, std::string& ret_msg);
    std::string serializeMessage(const Message& msg);
    std::string serializeMessage(const std::string& msg);
    bool deserializeMessage(const std::string& data, /*in*/
        std::string& ret_msg /*out*/);
public:
    typedef std::function<void(std::string, DeviceClient*)> Callback;
    DeviceClient() : serverSocket(INVALID_SOCKET), running(false) {}
    ~DeviceClient() {
        //stop();
    }

    // initialize Winsock
    bool initialize();
    void stopSockets(SOCKET socket);
    void stopSockets(std::string hostname);
    bool sendMessage(SOCKET socket, const Message& msg);
    bool sendMessage(std::string hostname, const std::string msg, std::string& ret_msg);
    // connect to server
    bool connectToServer(const std::string& ip, int port, const std::string& username);
    void setCallback(Callback cb)
    {
        f_callback = cb;
    }
};

