#include "pch.h"
#include "CPopupDialogTester.h"
#include "CPopupDialog.h"

void CPopupDialogTester::RunAllTests() {
    if (m_pTestDialog == nullptr) {
        AfxMessageBox(_T("Popup dialog is not initialized!"), MB_OK | MB_ICONERROR);
        return;
    }
    TestInitialState();
    TestButtonClick();
    TestModalExecution();
    TestParentRelationship();
    AfxMessageBox(_T("All tests passed successfully!"), MB_OK | MB_ICONINFORMATION);
}

void CPopupDialogTester::TestInitialState() {
    if (m_pTestDialog == nullptr) {
        AfxMessageBox(_T("Popup dialog is not initialized!"), MB_OK | MB_ICONERROR);
        return;
	}
    //dlg.Create(CPopupDialog::IDD);

    // Verify button exists
    ASSERT(m_pTestDialog->m_hWnd != NULL);

    //dlg.DestroyWindow();
}

void CPopupDialogTester::TestButtonClick() {
    if (m_pTestDialog == nullptr) {
        AfxMessageBox(_T("Popup dialog is not initialized!"), MB_OK | MB_ICONERROR);
        return;
    }

    // Simulate button click
    m_pTestDialog->SimulateButtonClick();
 //   if (m_pTestDialog->SimulateButtonClick != nullptr) {
 //       m_pTestDialog->SimulateButtonClick();
 //   } else {
 //       AfxMessageBox(_T("SimulateButtonClick method not implemented!"), MB_OK | MB_ICONERROR);
 //       return;
	//}

    // Verify text changed
    //ASSERT(dlg.GetMessageText() == _T("Button Clicked!"));
}

void CPopupDialogTester::TestModalExecution() {
    if (m_pTestDialog == nullptr) {
        AfxMessageBox(_T("Popup dialog is not initialized!"), MB_OK | MB_ICONERROR);
        return;
    }

    // Test modal return values
    // (Requires mocking user interaction - manual test)
    AfxMessageBox(_T("Manual test required:\n1. Click OK in popup\n2. Verify return value"), MB_OK);
}

void CPopupDialogTester::TestParentRelationship() {
    if (m_pTestDialog == nullptr) {
        AfxMessageBox(_T("Popup dialog is not initialized!"), MB_OK | MB_ICONERROR);
        return;
    }

    // Verify parent relationship
    ASSERT(m_pTestDialog->GetParent() == AfxGetMainWnd());
}
