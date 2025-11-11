#pragma once
#include "Scanner.h"
#include "CPopupDialog.h"
#include "afxcmn.h"
// recommended to use WM_APP instead of WM_USER for custom messages
#define WM_UPDATE_RESULT_LIST		(WM_APP + 1000)
#define WM_PROGRESS_START			(WM_UPDATE_RESULT_LIST + 2)
#define WM_PROGRESS_STEP_UPDATE		(WM_UPDATE_RESULT_LIST + 3)
#define WM_PROGRESS_CANCELLED		(WM_UPDATE_RESULT_LIST + 4)
#define WM_PROGRESS_COMPLETED		(WM_UPDATE_RESULT_LIST + 5)
#define WM_STATUSBAR_STATUS			(WM_UPDATE_RESULT_LIST + 6)
#define WM_STATUSBAR_PORT			(WM_UPDATE_RESULT_LIST + 7)
#define WM_STATUSBAR_IP				(WM_UPDATE_RESULT_LIST + 7)
#define WM_STATUSBAR_STEP			(WM_UPDATE_RESULT_LIST + 8)
#define WM_PORT_OPENED				(WM_UPDATE_RESULT_LIST + 9)
#define WM_DEBUG_INFO				(WM_UPDATE_RESULT_LIST + 100)
#define WM_TEST_ALL					(WM_UPDATE_RESULT_LIST + 101)


using CONNECT_CALLBACK = std::function<void(void* pParam)>;

enum class STATUS_PANE
{
	PANE_STATUS_TEXT = 0,
	PANE_STATUS_DETAIL,
	PANE_PORT_TEXT,
	PANE_PORT_VALUE,
	PANE_PROGRESS_TEXT,
	PANE_PROGRESS_STEP
};

typedef struct _STATUS_PARAM
{
	CString searchStatus;
	CString portValue;
	int currentStep;
	int maxStep;
} STATUS_PARAM;

class CSearchDialog : public CPopupDialog
{
	DECLARE_DYNAMIC(CSearchDialog)
public:
	CSearchDialog(CWnd* pParent = nullptr, SEARCH_TYPE type = SEARCH_TYPE::SEARCH_TYPE_COM);
	virtual ~CSearchDialog();
	// Override PostNcDestroy for cleanup
	virtual void PostNcDestroy() override;

	// prevent copying and assignment
	CSearchDialog(const CSearchDialog&) = delete;
	CSearchDialog& operator=(const CSearchDialog&) = delete;

	bool FoundInstrument();
	void SetSearchType(SEARCH_TYPE type) { m_searchType = type; }
	SEARCH_TYPE GetSearchType() const { return m_searchType; }
	void SetShowPercent(bool bShow) { m_bShowPercent = bShow; }
	void SetPaneAlignment(int index, UINT alignment)
	{
		if (index >= 0 && index < (int)m_paneAlignments.GetCount())
			m_paneAlignments[index] = alignment;
	}
	void SetPaneText(int index, const CString& text)
	{
		if (index >= 0 && index < (int)m_paneTexts.GetCount())
			m_paneTexts[index] = text;
	}
	CString GetPaneText(int index) const
	{
		if (index >= 0 && index < (int)m_paneTexts.GetCount())
			return m_paneTexts[index];
		return _T("");
	}
	CString GetSelectedString();
	void SetConnectCallback(const CONNECT_CALLBACK& callback) { m_connectCallback = callback; }
	/**
	* @function SetSearchDeviceIds
	* @brief Sets the device IDs to search for, provided as a semicolon-separated(default) string.
	*/
	void SetSearchDeviceIds(const CStringA& devIds);
	/**
	* @function SetDelimiter
	* @brief Sets the delimiter character used to separate device IDs in the input string.
	*/
	void SetDelimiter(char delimiter) { m_cDelimiter = delimiter; }
protected:
	CButton m_buttonStart;
	CFont m_font;
	SEARCH_TYPE m_searchType;
	mutable bool m_bSearchInProgress;
	CProgressCtrl m_progressCtrl;
	CListBox m_resultList;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog() override;
	void InitializeStatusBar();
	bool IsSearchedDeviceId(const CString& devId) const;
#ifdef _DLG_DEBUG
	virtual void SimulateButtonClick();
#endif
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLbnDblclkResultList();
	afx_msg void OnLbnSelchangeResultList();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBnClickedConfirm();
protected:
	afx_msg LRESULT OnUpdateSearchStatus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateResultList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSearchCancelled(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSearchComplete(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProgressStart(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProgressStepUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateStatusBarStatus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateStatusBarPort(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateStatusBarStep(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPortOpened(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDebugInfo(WPARAM wParam, LPARAM lParam);
private:
	int m_iMaxValue;
	CStatusBarCtrl m_statusBar;
	CUIntArray m_paneAlignments;
	CStringArray m_paneTexts;
	int m_ResultCount;
	bool m_bShowPercent;
	CString m_SelectedString;
	CONNECT_CALLBACK m_connectCallback;
	std::vector<CStringA> m_searchDeviceIds;
	char m_cDelimiter = ';';
};

