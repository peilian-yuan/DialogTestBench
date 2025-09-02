
// DialogTestBenchDlg.h: Headerdatei
//

#pragma once


// CDialogTestBenchDlg-Dialogfeld
class CPopupDialog; // Vorwärtsdeklaration für das Popup-Dialogfeld
class CDialogTestBenchDlg : public CDialogEx
{
	bool m_bPercent;
	bool m_bIpScan;
public:
	CDialogTestBenchDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGTESTBENCH_DIALOG };
#endif
	void SetShowPercent(bool b) { m_bPercent = b; }
	bool GetShowPercent() const { return m_bPercent; }
	void SetIpScan(bool b) { m_bIpScan = b; }
	bool IsIpScan() const { return m_bIpScan; }

// Implementierung
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung

	HICON m_hIcon;
	CPopupDialog* m_pPopupDialog; // Zeiger auf das Popup-Dialogfeld

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenPopupDialog();
	afx_msg void OnBnClickedRunTests();
};
