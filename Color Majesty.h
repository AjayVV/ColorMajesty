#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

class CColorMajestyApp : public CWinApp
{
public:
	CColorMajestyApp() = default;

	CColorManager ColorManager;

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CColorMajestyApp theApp;

bool CopyToClipboard(LPCWSTR lpText2Copy, CWnd* pWnd = AfxGetMainWnd());

#define GetColorManager() theApp.ColorManager