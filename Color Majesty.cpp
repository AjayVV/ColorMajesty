#include "stdafx.h"
#include "Color Majesty.h"
#include "Color MajestyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CColorMajestyApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// The one and only CColorMajestyApp object
CColorMajestyApp theApp;


BOOL CColorMajestyApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	ColorManager.LoadColors();

	CColorMajestyDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

bool CopyToClipboard(LPCWSTR lpText2Copy, CWnd* pWnd)
{
	ASSERT(lpText2Copy);
	ASSERT(pWnd);

	if (!pWnd->OpenClipboard())
		return false;

	if (!EmptyClipboard())
	{
		CloseClipboard();
		return false;
	}


	const int nLenInBytes = wcslen(lpText2Copy);
	HGLOBAL hCopy = GlobalAlloc(GMEM_MOVEABLE, nLenInBytes);
	if (hCopy == nullptr)
	{
		CloseClipboard();
		return false;
	}

	//#pragma warning(disable:6011)
	LPSTR lpCopy = static_cast<LPSTR> (GlobalLock(hCopy));
	memcpy(lpCopy, lpText2Copy, nLenInBytes);

	lpCopy[nLenInBytes] = (CHAR)0;    // null character
	GlobalUnlock(hCopy);
	//#pragma  warning(default:6011)

	// Place the handle on the clipboard.

	SetClipboardData(CF_TEXT, hCopy);

	CloseClipboard();

	return true;
}
