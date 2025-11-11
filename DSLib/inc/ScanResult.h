#pragma once
#include <afxwin.h>
#include <vector>
#include "Scanner.h"

class ScanResult
{
	std::string m_devId;
	std::string m_sn;
protected:
	std::string m_name;
public:
	ScanResult() : m_devId(""), m_sn(""), m_name("") {}
	// copy constructor
	ScanResult(const ScanResult& r) : m_devId(r.m_devId), m_sn(r.m_sn), m_name(r.m_name)
	{
	}
    // Durch die korrekte Zuweisungsoperator-Definition:
    ScanResult& operator=(const ScanResult& r)
    {
        if (this != &r)
        {
			m_name = r.m_name;
            m_devId = r.m_devId;
            m_sn = r.m_sn;
        }
        return *this;
    }
	virtual ~ScanResult() {}
	virtual std::string GetCombinedResultString() { return ""; }
	std::string GetName() const { return m_name; }
	void SetDeviceId(const CString& parseString);
	void SetSerialNumber(const CString& parseString);
	void SetDeviceId(const std::string& parseString) { m_devId = parseString; }
	void SetSerialNumber(const std::string& parseString) { m_sn = parseString; }
	std::string GetDeviceId() const { return m_devId; }
	std::string GetSerialNumber() const { return m_sn; }
	static std::string ConvertToString(const CString& cstr);
	static CString ConvertToCString(const std::string& str);
	static bool IsAllDigital(std::string& str);
};
using RESULTS = std::vector<ScanResult>;

class ComportResult : public ScanResult
{
public:
	ComportResult() : ScanResult() {}
	ComportResult(const ComportResult& r) : ScanResult(r) {}
	void SetPortName(const CString& parseString);
	void SetPortName(const std::string& parseString) { m_name = parseString; }
	std::string GetPortName() const { return m_name; }
	virtual std::string GetCombinedResultString() override;
};

class IpScanResult : public ScanResult
{
public:
	IpScanResult() : ScanResult() {}
	IpScanResult(const IpScanResult& r) : ScanResult(r)
	{
	}
	void SetIp(const CString& parseString);
	void SetIp(const std::string& parseString) { m_name = parseString; }
	std::string GetIp() const { return m_name; }
	virtual std::string GetCombinedResultString() override;
};


class ScanResults : public ScanResult
{
	static ScanResults* s_instance;
	static std::mutex s_mutex;
	RESULTS m_Results;
	ScanResults() {}
	virtual ~ScanResults() { m_Results.clear(); }
public:
	// Delete copy constructor and assignment operator
	ScanResults(const ScanResults&) = delete;
	ScanResults& operator=(const ScanResults&) = delete;

	static ScanResults* GetScanResults();
	/**
	* @function Release
	* @brief Releases the static singleton instance of ScanResults.
	* @note This method must be called to free static resources when done using ScanResults.
	*/
	static void Release();
	RESULTS GetScanResultData();
	void AddResult(const ScanResult& result);
	void SetResult(UINT Idx, const ScanResult& result);
	bool GetResult(UINT idx, ScanResult& result);
	bool GetResult(CString selString, ScanResult& result);
	bool GetLastResult(ScanResult& result);
	bool HasItem(const std::string& name);
	bool HasResult();
	void ClearResults();
	size_t GetResultCount();

};
