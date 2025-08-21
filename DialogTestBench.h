
// DialogTestBench.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CDialogTestBenchApp:
// Siehe DialogTestBench.cpp für die Implementierung dieser Klasse
//

class CDialogTestBenchApp : public CWinApp
{
public:
	CDialogTestBenchApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CDialogTestBenchApp theApp;
