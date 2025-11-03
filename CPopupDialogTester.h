#pragma once
class CPopupDialog;
class CPopupDialogTester
{
	/*
	* @brief this member variable holds the pointer to the dialog that will be tested
	* @note the class must be initialized from CPopupDialog and CDialogTester
	*/
	CPopupDialog* m_pTestDialog; // pointer to be tested dialog
public:
	CPopupDialogTester(CPopupDialog* pPopupDialog) : m_pTestDialog(pPopupDialog) {}
	void RunAllTests();
protected:
	virtual void TestInitialState();
	virtual void TestModalExecution();
	virtual void TestParentRelationship();
#ifdef _DLG_DEBUG
	virtual void TestButtonClick();
#endif // _DLG_DEBUG
};

