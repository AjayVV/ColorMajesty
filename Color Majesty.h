
// Color Majesty.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CColorMajestyApp:
// See Color Majesty.cpp for the implementation of this class
//

class CColorMajestyApp : public CWinApp
{
public:
	CColorMajestyApp();

	CColorManager ColorManager;

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CColorMajestyApp theApp;

bool CopyToClipboard(LPCWSTR lpText2Copy, CWnd* pWnd = AfxGetMainWnd());

#define GetColorManager() theApp.ColorManager