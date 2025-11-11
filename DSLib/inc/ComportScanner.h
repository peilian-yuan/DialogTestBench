#pragma once
#include <Windows.h>
#include "Scanner.h"

#define COMMAND_START ":0F03"
#define COMMAND_ADDR 5
#define COMMAND_END "\r\n"
#define REQUEST_END "??\r\n"
#define DEV_ID_POS	7

using PORTS = std::vector<std::wstring>;
/**
* @class ComportScanner
* @brief Scans for available COM ports and tests connections. Only read commands are supported.
*/
class CPopupDialog;
class ComportScanner : public Scanner
{
public:
	ComportScanner(CPopupDialog* pDlg = nullptr);
	virtual ~ComportScanner() {};
	DWORD GetBaudRate() const
	{
		return m_dwBaudRate;
	}
	/**
	* @function GetAvailableComPorts
	* @brief Scans for available COM ports and stores them in m_Ports vector.
	* @return true if at least one COM port is found, false otherwise.
	*/
	bool GetAvailableComPorts();
	bool EnumeratePortsUsingSetupAPI();
	bool EnumeratePortsUsingRegistry();
	bool EnumeratePortsByDirectAccess();
	PORTS GetPorts() const { return m_Ports; }
	bool TestComPortConnection(const std::wstring& portName);
	/**
	* @function StartScan
	* @brief Tests the connection to a specified COM port by sending a command and receiving a response.
	* @param portName The name of the COM port to test (e.g., "COM3").
	* @param response A reference to a string where the response will be stored.
	* @param command The command to send to the COM port. If empty, default command: read device ID "0000000A".
	*/
	virtual bool StartScan() override;
	virtual bool ParseResponse(std::string& response, std::string& foundstr);
	virtual bool CloseConnection();
	virtual void StopScan();
	virtual void SendScanMessage(unsigned int msgID) override;
	virtual void SendScanMessage(unsigned int msgID, CString message) override;
	virtual void SendScanMessage(unsigned int msgID, std::string message) override;
	virtual void SendScanMessage(unsigned int msgID, DWORD dwNum) override;

protected:
	CONNECTION_STATE m_State; // Current state of the COM port
	/**
	* @function to_string
	* @brief Converts a wide string (wstring) to a standard string (string).
	* @param wstr The wide string to convert.
	* @return The converted standard string.
	*/
	bool initializeDCB(HANDLE& hCom, DWORD baudRate = CBR_115200);
	bool SetTimeout(bool bForResp = false);
	std::string ReadExistingData(HANDLE hCom, DWORD timeoutMs);

	virtual bool Receive(std::string portName, int iIndex = 0);
	virtual bool SendCommand(int iIndex, std::string portName, const RECEIVE& Callback);
	HANDLE m_hCom;
private:
	DCB m_dcb;
	PORTS m_Ports;
	DWORD m_dwBaudRate;
	// only part of the command, without start and end: Address + Read Size; Example: "0000000A"
	CPopupDialog* m_pParentDlg;
};

