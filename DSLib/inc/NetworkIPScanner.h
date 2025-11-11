#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <winsock2.h>

class NetworkIPScanner
{
public:
    NetworkIPScanner() : timeout(300) {}
    void scanAllLocalNetworks();
    auto getNetworks() { return m_Networks; }
    void setTimeout(DWORD ms) { timeout = ms; }
    // convert IP address to 32 bytes integer
    uint32_t ipToUint(const std::string& ip);
    // convert 32 bytes integer to IP address
    std::string uintToIp(uint32_t ip);
protected:
    // get all ip range in local network
    bool getLocalNetworks();
    std::string calculateNetworkAddress(const std::string& ip, const std::string& mask);
    std::string calculateBroadcastAddress(const std::string& ip, const std::string& mask);

private:
    // timeout ms
    DWORD timeout;
    std::vector<std::pair<std::string, std::string>> m_Networks;

};
