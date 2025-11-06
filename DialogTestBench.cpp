
// DialogTestBench.cpp: Definiert das Klassenverhalten für die Anwendung.
//

#include "pch.h"
#include "framework.h"
#include "DialogTestBench.h"
#include "DialogTestBenchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDialogTestBenchApp

BEGIN_MESSAGE_MAP(CDialogTestBenchApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDialogTestBenchApp-Erstellung

void CDialogTestBenchApp::Usage(LPWSTR prog)
{
	CString msg;
	msg.Format(_T("Usage: %s [-h] [-p] [-c|-i] [-d DEV_IDS]\n")
		_T("  -h : Show help\n")
		_T("  -p : Show percentage in progress bar\n")
		_T("  -c : Scan COM ports (default)\n")
		_T("  -i : Scan IP addresses\n")
		_T("  -d : String of searched device ids\n")
		_T("\nExample: %s -p -i\n"), prog, prog);
	AfxMessageBox(msg, MB_ICONINFORMATION);
}

CDialogTestBenchApp::CDialogTestBenchApp()
{
	// Neustart-Manager unterstützen
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance positionieren
}


// Das einzige CDialogTestBenchApp-Objekt

CDialogTestBenchApp theApp;


// CDialogTestBenchApp-Initialisierung

BOOL CDialogTestBenchApp::InitInstance()
{
	// InitCommonControlsEx() ist für Windows XP erforderlich, wenn ein Anwendungsmanifest
	// die Verwendung von ComCtl32.dll Version 6 oder höher zum Aktivieren
	// von visuellen Stilen angibt.  Ansonsten treten beim Erstellen von Fenstern Fehler auf.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Legen Sie dies fest, um alle allgemeinen Steuerelementklassen einzubeziehen,
	// die Sie in Ihrer Anwendung verwenden möchten.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Shell-Manager erstellen, falls das Dialogfeld
	// Shellbaumansicht- oder Shelllistenansicht-Steuerelemente enthält.
	CShellManager *pShellManager = new CShellManager;

	//Visuellen Manager "Windows Native" aktivieren, um Designs für MFC-Steuerelemente zu aktivieren
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht verwenden und die Größe
	// der ausführbaren Datei verringern möchten, entfernen Sie
	// die nicht erforderlichen Initialisierungsroutinen.
	// Ändern Sie den Registrierungsschlüssel, unter dem Ihre Einstellungen gespeichert sind.
	// TODO: Ändern Sie diese Zeichenfolge entsprechend,
	// z.B. zum Namen Ihrer Firma oder Organisation.
	SetRegistryKey(_T("Vom lokalen Anwendungs-Assistenten generierte Anwendungen"));
	
	// Argumente der Befehlszeile abrufen
	TCHAR* pCommandLine = ::GetCommandLine();
	int nArgc = 0;
	LPWSTR* pArgv = ::CommandLineToArgvW(pCommandLine, &nArgc);
	bool bPercent = false;
	bool bIpScan = true;
	CStringA devid;
	if (nArgc > 1)
	{
		// Es wurden Befehlszeilenargumente übergeben
		// Das erste Argument (pArgv[0]) ist der Programmname
		// Weitere Argumente können hier verarbeitet werden
		for (int i = 1; i < nArgc; ++i)
		{
			// Beispiel: Argumente ausgeben
			TRACE(_T("Argument %d: %s\n"), i, pArgv[i]);
			if (pArgv[i][0] == L'-')
			{
				// percentage or number of ports
				if (_wcsicmp(&pArgv[i][1], L"p") == 0)
				{
					bPercent = true;
				}
				else if (_wcsicmp(&pArgv[i][1], L"c") == 0)
				{
					// COM-Port Scan
					bIpScan = false;
				}
				else if (_wcsicmp(&pArgv[i][1], L"i") == 0)
				{
					bIpScan = true; // IP-Scan
				}
				else if (_wcsicmp(&pArgv[i][1], L"d") == 0)
				{
					// set searched device id
					devid = CW2A(pArgv[++i]);
				}
				else if (_wcsicmp(&pArgv[i][1], L"h") == 0)
				{
					Usage(pArgv[0]);
					return FALSE;
				}
				else
				{
					// Unbekannter Schalter
					Usage(pArgv[0]);
					return FALSE;
				}
			}
			else
			{
				// Normales Argument
				Usage(pArgv[0]);
				return FALSE;
			}
			// Hier können Sie die Argumente weiterverarbeiten
		}
	}
	else
	{
		bPercent = false;
		// COM-Port Scan
		bIpScan = false;
	}

	CDialogTestBenchDlg dlg;
	dlg.SetShowPercent(bPercent);
	dlg.SetIpScan(bIpScan);
	dlg.SetSearchedDevIds(devid);
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Fügen Sie hier Code ein, um das Schließen des
		//  Dialogfelds über "OK" zu steuern
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Fügen Sie hier Code ein, um das Schließen des
		//  Dialogfelds über "Abbrechen" zu steuern
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warnung: Fehler bei der Dialogfelderstellung, unerwartetes Beenden der Anwendung.\n");
		TRACE(traceAppMsg, 0, "Warnung: Wenn Sie MFC-Steuerelemente im Dialogfeld verwenden, ist #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS nicht möglich.\n");
	}

	// Den oben erstellten Shell-Manager löschen.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Da das Dialogfeld geschlossen wurde, FALSE zurückliefern, sodass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}

