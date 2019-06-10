
// Color Majesty.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Color Majesty.h"
#include "Color MajestyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorMajestyApp

BEGIN_MESSAGE_MAP(CColorMajestyApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CColorMajestyApp construction

CColorMajestyApp::CColorMajestyApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CColorMajestyApp object

CColorMajestyApp theApp;


// CColorMajestyApp initialization

BOOL CColorMajestyApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	ColorManager.LoadColors();

	CColorMajestyDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}




bool CopyToClipboard(LPCWSTR lpText2Copy, CWnd* pWnd)
{
	ASSERT(lpText2Copy);
	ASSERT(pWnd);

	if(!pWnd->OpenClipboard())
		return false;

	if(!EmptyClipboard())
	{
		CloseClipboard();
		return false;
	}


	const int nLenInBytes = wcslen(lpText2Copy) ;
	HGLOBAL hCopy= GlobalAlloc(GMEM_MOVEABLE, nLenInBytes);
	if (hCopy== NULL)
	{
		CloseClipboard();
		return false;
	}

	//#pragma warning(disable:6011)
	LPSTR lpCopy = static_cast<LPSTR> ( GlobalLock(hCopy) );
	memcpy(lpCopy , lpText2Copy, nLenInBytes);

	lpCopy[nLenInBytes] = (CHAR) 0;    // null character
	GlobalUnlock(hCopy);
	//#pragma  warning(default:6011)

	// Place the handle on the clipboard.

	SetClipboardData(CF_TEXT, hCopy);

	CloseClipboard();

	return true;
}
