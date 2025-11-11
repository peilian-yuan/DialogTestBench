#pragma once
#include <vector>
#include <string>
#include <winsock2.h>
#include "NetworkIPScanner.h"
#include "Scanner.h"

/*
* DeviceScanner.h
* brief scanning local networks and find the IP address of the device which is connected
* 
*/

enum class DEVICE_CRITIC
{
    DEV_MANUFACTURER,   // manufacture
    DEV_HOST_NAME,      // hostname
    DEV_MAC             // mac address
};

// struct for device info 
struct _DevInfo {
    std::string ip;
    std::string mac;
    std::string hostname;
    std::string manufacturer;
    bool isTarget = false;
};
typedef struct _DevInfo DeviceInfo;

class AutoIpDetector;
class DeviceScanner
{
public:
    DeviceScanner() 
		: m_pDetector(nullptr)
        , timeout(500)
        , maxThreads(50) {} // default timeout 500ms
	void setDetector(AutoIpDetector* pDetector) { m_pDetector = pDetector; }
    void setMaxThreads(int max) { maxThreads = max; }
    void setTimeout(DWORD ms) { timeout = ms; }
    void scanAllDevicesLocalNetworks();
    auto getAllDevices() { return m_allDevices; }
    std::vector<DeviceInfo> findDevice(std::vector<DeviceInfo> foundDevices,
                                        const std::string& targetDevice,
                                        DEVICE_CRITIC critic);
    std::vector<DeviceInfo> findDevice(const std::string& baseIP, int start, int end,
                                        const std::string& targetDevice,
                                        DEVICE_CRITIC critic);

    std::vector<DeviceInfo> scanNetworkRangeDevices(const std::string& startIP, const std::string& endIP);
    std::string lookupManufacturer(BYTE b1, BYTE b2, BYTE b3);
    void printDeviceInfo(const DeviceInfo& info);
private:
    std::vector<std::string> scanActiveIPs(const std::string& baseIP, int start, int end);
    std::vector<std::string> scanActiveIPs(uint32_t startIP, uint32_t endIP);
    bool ping(const std::string& ip);

    std::string normalizeMAC(const std::string& mac);
    bool getIpAddress(const std::string& ip);
    std::string getHostname(const std::string& ip);
    bool containsIgnoreCase(const std::string& str, const std::string& substr);
    std::vector<DeviceInfo> getDeviceDetails(const std::vector<std::string>& ips);
    DeviceInfo getSingleDeviceInfo(const std::string& ip);
    void getMACAndManufacturer(const std::string& ip, std::string& mac, std::string& manufacturer);

    // max number of threads
    int maxThreads;
    DWORD timeout; // timeout ms
    NetworkIPScanner m_NetworkScanner;
    std::vector<DeviceInfo> m_allDevices;
    AutoIpDetector* m_pDetector;
};

