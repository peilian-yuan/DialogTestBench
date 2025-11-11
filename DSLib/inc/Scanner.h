#pragma once
#include <afxwin.h>
#include <map>
#include <vector>
#include <list>
#include <string>
#include <mutex>
#include <functional>
#ifdef _DEBUG
#include "ResourceTracker.h"
#endif // _DEBUG
// type of results: (Com-Port-Name, Response)

typedef std::function<bool(std::string, int)>  RECEIVE;

enum class SEARCH_TYPE
{
	SEARCH_TYPE_COM = 0,
	SEARCH_TYPE_IP
};

typedef struct _RESULT
{
	std::string portName; // COM-Port-Name or IP address
	std::string devId;
	std::string sn;
} RESULT;

enum class CONNECTION_STATE
{
	CONN_DISCONNECTED,
	CONN_SCANNING,
	CONN_CLOSED,
	CONN_CLOSING,
	CONN_IDLE,
	CONN_CONNECTED,
	CONN_CONNECTING,
	CONN_ERROR
};

class Scanner
{
protected:
	CString m_lastMessage;
public:
	static std::mutex ScannerMutex; // Mutex for thread safety
	static void SetCancelled();
	static bool IsCancelled();
	Scanner(SEARCH_TYPE eSearchType) : m_searchType(eSearchType), m_lastMessage(_T("")) {}
	virtual ~Scanner() = default;
	// Method to start scanning
	virtual bool StartScan();
	// Method to stop scanning
	virtual void StopScan() = 0;
	// Method to check if scanning is in progress
	virtual bool CloseConnection() = 0;
	// Method to send a command to the device
	virtual bool SendCommand(int iIndex, std::string portName, const RECEIVE& fReceive) = 0;
	// Method to read response from the device after sending a command
	virtual bool Receive(std::string portName, int iIndex) = 0;
	// Method to parse response from the device
	virtual std::string ParseResponse(std::string& response) { return ""; }
	virtual bool ParseResponse(std::string& response, std::string& foundstr) { return true; }
	// Method to send message to parent dialog
	virtual void SendScanMessage(unsigned int msgID) {};
	virtual void SendScanMessage(unsigned int msgID, std::string message) {};
	virtual void SendScanMessage(unsigned int msgID, CString message) {};
	virtual void SendScanMessage(unsigned int msgID, DWORD dwNum) {};
	// Callback method to handle messages (can be overridden in derived classes)
	virtual bool OnMessage(unsigned int msgID, std::string message) { return true; }
	// set new command list to be sent to the device
	void SetTestCommands(const std::vector<std::string>& commands) { m_Commands = commands; }
	// set new command at specified index to be sent to the device; if index < 0, clear all commands
	void SetTestCommand(int iIndex, std::string cmd) { 
		if (iIndex >= 0 && iIndex < (int)m_Commands.size())
			m_Commands[iIndex] = cmd;
		else if (iIndex < 0)
			m_Commands.clear();
		else
			TRACE0("Error: index is out of range!\n");
	}
	// add the command  at end of command list to be sent to the device
	void AddTestCommand(const std::string& command) { m_Commands.push_back(command); }
	// clear all test commands
	void ClearTestCommands() { m_Commands.clear(); }
	// get (iIndex)th command
	std::string GetTestCommand(int iIndex) const { 
		if (iIndex >= 0 && iIndex < (int)m_Commands.size())
			return m_Commands[iIndex];
		return "";
	}
protected:
	std::vector <std::string> m_Commands;
private:
	static bool m_bCancelled; // Flag to cancel the operation
	SEARCH_TYPE m_searchType;
};
#define SCANN_LOCK std::lock_guard<std::mutex> lock(Scanner::ScannerMutex)

