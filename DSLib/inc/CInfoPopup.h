#pragma once
#include <afxwin.h>
#include <afxpriv.h>
#include <afxtempl.h>
#include <process.h> // For _beginthreadex
#include <functional>
#include <string>
#define WM_UPDATE_STATUS    WM_USER + 120 
#define WM_UPDATE_MESSAGE   WM_USER + 121 
/**
* Usage:
* 1. create a dialog resource by VS widget
* 2. implement event WM_UPDATE_STATUS in the user codes
* 3. implement WM_UPDATE_MESSAGE in the user codes if neccessary (option)
* 4. create instance of CInfoPopup: CInfoPopup* m_pDlg = new CInfoPopup(IDD_WAIT, pParent);
* 5. create dialog window: CreatePopupDialog()
* 6. create callback function for running detection
* 7. start running detection
* 8. show popup dialog
* 
* public functions:
* - BOOL InitializeDialog()
* - void SetBackgroundColor(COLORREF bgColor, COLORREF fgColor)
* - void SetMessageFont(LPCTSTR lpszFaceName, int nPointSize)
* - void SetMessage(LPCTSTR msg, bool center = true)
* - void RunFunctionAndClose(std::function<void()> func, bool block = true)
* 
* The following messages can implemented in the user side if they are needed.
* 
* Update parent window after the user process ends:                 ON_MESSAGE(WM_UPDATE_STATUS, OnUpdateStatus)
* Update message on pupup window during user process is running:    ON_MESSAGE(WM_UPDATE_MESSAGE, OnUpdateMessage)
*/
class CInfoPopup : public CDialog {
public:

    CInfoPopup(UINT IDD, CWnd* pParent = nullptr);

    //~CInfoPopup() {}

    void SetBackgroundColor(COLORREF bgColor, COLORREF fgColor);

    BOOL InitializeDialog();

    void SetMessageFont(LPCTSTR lpszFaceName, int nPointSize);

    void SetMessage(LPCTSTR msg, bool center = true);

    void RunFunctionAndClose(std::function<void()> func, bool block = true);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

protected:
    UINT m_IDD;
    CString m_strMessage;
    CStatic m_static;
    CBrush m_brushBkg; // background brush
    LPCTSTR m_lpszFontFaceName;
    int m_nFontPointSize;
    COLORREF m_crBgColor;
    COLORREF m_crFgColor;

    virtual BOOL OnInitDialog() override;

    afx_msg void OnClose();
    // Override PostNcDestroy for proper cleanup
    virtual void PostNcDestroy() override;

    std::function<void()> m_func;

private:
    // run function with blocking
    static UINT __cdecl RunFunction(LPVOID pParam);

    // run function without blocking
    static UINT __cdecl ThreadProc(LPVOID pParam);
    DECLARE_MESSAGE_MAP()
};

/**
* default color of background of dialog : grey
* default text color: black
* default font of message: Arial
* default size of font: 12
*/
CInfoPopup* CreatePopupDialog(UINT IDD,
    CWnd* pParent,
    COLORREF crBgRGBColor = 0,
    COLORREF crFgRGBColor = 0,
    LPCTSTR lpszFaceName = _T("Arial"),
    int nPointSize = 12);
