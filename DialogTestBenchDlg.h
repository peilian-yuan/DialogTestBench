
// DialogTestBenchDlg.h: Headerdatei
//

#pragma once


// CDialogTestBenchDlg-Dialogfeld
class CPopupDialog; // Vorwärtsdeklaration für das Popup-Dialogfeld
class CDialogTestBenchDlg : public CDialogEx
{
public:
	CDialogTestBenchDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGTESTBENCH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
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
