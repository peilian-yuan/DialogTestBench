#pragma once
#include <afxwin.h>
#include <functional>
#include "ScanResult.h"

using TASK_FUNCTION = std::function<bool()>;

// CPopupDialog-Dialog
class CPopupDialog : public CDialog
{
	DECLARE_DYNAMIC(CPopupDialog)
	CWnd* m_pParentWnd; // Pointer to parent window
	LPCTSTR m_lpszFontFaceName;
	int m_nFontPointSize;
public:
	CPopupDialog(UINT IDD = 0, CWnd* pParent = nullptr);
	virtual ~CPopupDialog();

	CWnd* GetParentWnd() const { return m_pParentWnd; }
	void SetTaskFunction(TASK_FUNCTION func) { m_TaskFunction = func; }
	void RunFunctionAndClose(bool block = true);
	void SetCloseAfterNoPortFound(bool bClose = false) { m_bCloseAfterNoPortFound = bClose; }
	bool IsCloseAfterNoPortFound() const { return m_bCloseAfterNoPortFound; }
	//BOOL InitializeDialog();
	// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH };
#endif
#ifdef _DLG_DEBUG
	virtual void SimulateButtonClick() = 0;
#endif // _DLG_DEBUG

protected:
	bool m_bInit;
	TASK_FUNCTION m_TaskFunction; // Callback function to run in the dialog thread

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog() override;

private:
	bool m_bCloseAfterNoPortFound;
	// run function with blocking
	static UINT __cdecl RunFunction(LPVOID pParam);

	// run function without blocking
	static UINT __cdecl ThreadProc(LPVOID pParam);

	DECLARE_MESSAGE_MAP()
};
