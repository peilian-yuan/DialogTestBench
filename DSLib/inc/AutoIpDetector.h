#pragma once
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "Scanner.h"
#include "DeviceScanner.h"
#include "DeviceClient.h"
/*
* class AutoIpDetector
* brief automatically detect device ip in the local networks. It is also possible to send commands to device in order to obtain
*       neccessary properties from the connected device.
* Usage:
*       0. create instance: ins AutoIpDetector
*       1. check administrator right (option): CheckAdminRight()
*       2. add checking manufacturer command and its valid answer: AddCheckManufacturerCommand()
*       3. add checking model command and its valid answer: AddCheckModelCommand()
*       4. scan connected devices in local networks: ScanDevices()
*       5. detect target ips by using checking commands: DetectTargetIps()
* other functions:
*       - AddCheckManufacturerCommand(): add command for checking manufacturer
*       - AddCheckModelCommand(): add command for checking model
*       - GetManufacturerCommand()
*       - GetManufacturerAnswer()
*       - GetModelCommand()
*       - GetModelAnswer()
*       - GetFoundDevices(): get zwitch data of scanned devices
*       - GetDetectedIps():  get result of detected ips, default port: 10001
*/
enum CheckCommand
{
	CC_MODEL,
	CC_MANUF
};

class CPopupDialog;
class AutoIpDetector : public Scanner
{
	std::vector<std::string> m_DetectedIps;
	std::vector<DeviceInfo> m_FoundDevices;
	DeviceScanner m_Scanner;
	DeviceClient m_Client;
	int m_Port;
	std::string m_TargetChip;
	DEVICE_CRITIC m_eCritic;
	CPopupDialog* m_pParentDlg;
	std::function<void()> m_pfCallback;
public:
	virtual bool StartScan() override;
	virtual void StopScan() override {};
	virtual bool CloseConnection() { return true; };
	// Method to send a command to the device
	virtual bool SendCommand(int iIndex, std::string portName, const RECEIVE& fReceive) override { return true; };
	// Method to read response from the device after sending a command
	virtual bool Receive(std::string portName, int iIndex) override { return true; };
	// Method to parse response from the device
	virtual std::string ParseResponse(std::string& response) override { return ""; };
	virtual void SendScanMessage(unsigned int msgID) override;
	virtual void SendScanMessage(unsigned int msgID, CString message) override;
	virtual void SendScanMessage(unsigned int msgID, DWORD dwNum) override;

	void SetTargetChip(std::string chip) { m_TargetChip = chip; }
	void SetCritic(DEVICE_CRITIC critic) { m_eCritic = critic; }
	void SetCallback(std::function<void()> pfCallback) { m_pfCallback = pfCallback; }

	AutoIpDetector(CPopupDialog* pDlg = nullptr);
	void SetPort(int port)
	{
		m_Port = port;
	}
	bool CheckAdminRight();
	std::vector<DeviceInfo> GetFoundDevices();
	std::vector<std::string> GetDetectedIps() {
		return m_DetectedIps;
	}

	void ScanDevices(std::string target, DEVICE_CRITIC critic);
protected:
	void DetectTargetIps();
};

