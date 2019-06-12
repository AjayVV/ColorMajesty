#include "stdafx.h"
#include "Color Majesty.h"
#include "Color MajestyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CColorMajestyDlg dialog
CColorMajestyDlg::CColorMajestyDlg() : CDialog(CColorMajestyDlg::IDD),
ColorManager(GetColorManager())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorMajestyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLORIN, m_cColorInput);
	DDX_Control(pDX, IDC_COLOR_DISP, m_cColorList);
	DDX_Control(pDX, IDC_PREVIEW, m_cPreviewWnd);
}

BEGIN_MESSAGE_MAP(CColorMajestyDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_COLORIN, &CColorMajestyDlg::OnEnChangeColorin)
	ON_WM_MEASUREITEM()
	//ON_WM_SIZE()
	ON_BN_CLICKED(IDC_COPYRGB, &CColorMajestyDlg::OnBnClickedCopyrgb)
	ON_COMMAND(IDC_ADD2VIEW, OnAdd2View)
	// ON_COMMAND(WM_USER+1, &CColorMajestyDlg::OnBnClickedCopyrgb)
	ON_BN_CLICKED(IDC_COPYHEX, &CColorMajestyDlg::OnBnClickedCopyhex)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_RCLICK, IDC_COLOR_DISP, &CColorMajestyDlg::OnRclickColorDisp)
	ON_NOTIFY(NM_CLICK, IDC_ADD2VIEW, &CColorMajestyDlg::OnNMClickAdd2view)
END_MESSAGE_MAP()

BOOL CColorMajestyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateContextMenus();

	//BOOL bOk = m_cWndResizer.Hook(this);
	//ASSERT(bOk == TRUE);

	//m_cWndResizer.SetAnchor(IDC_COLOR_DISP,  ANCHOR_BOTTOM | ANCHOR_TOP|ANCHOR_HORIZONTALLY);
	//m_cWndResizer.SetAnchor(IDC_SHOWRGB, ANCHOR_BOTTOM|ANCHOR_RIGHT);
	//m_cWndResizer.SetAnchor(IDC_SHOWHSL, ANCHOR_BOTTOM|ANCHOR_RIGHT);
	//m_cWndResizer.SetAnchor(IDC_SHOWHEX, ANCHOR_BOTTOM|ANCHOR_RIGHT);
	//m_cWndResizer.SetAnchor(IDC_SHOWPERCENT, ANCHOR_BOTTOM|ANCHOR_RIGHT);

	//m_cWndResizer.SetAnchor(IDC_COPYRGB, ANCHOR_RIGHT);	
	//m_cWndResizer.SetAnchor(IDC_COPYHEX, ANCHOR_RIGHT);	

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_cColorList.InsertColumn(0, L"Color", LVCFMT_LEFT, 300);

	ShowWindow(SW_MAXIMIZE);
	ShowWindow(SW_RESTORE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CColorMajestyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CColorMajestyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CColorMajestyDlg::OnEnChangeColorin()
{
	CString strInput;
	m_cColorInput.GetWindowTextW(strInput);

	ColorManager.BeginSearch(strInput);

	m_cColorList.Clear();


	while (ColorManager.FindNext())
	{
		const ColorInfo& color_info = ColorManager.GetNext();

		m_cColorList.InsertItem(color_info);
	}

}


void CColorMajestyDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if (IDC_COLOR_DISP == nIDCtl)
	{
		lpMeasureItemStruct->itemHeight = SQUARE_SIZE + SQUARE_MARGIN * 2;
	}

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


void CColorMajestyDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (::IsWindow(m_cColorList.m_hWnd))
	{
		m_cColorList.MoveWindow(8, 40, cx - 170, cy - 10 - 40, TRUE);
	}
}


void CColorMajestyDlg::OnBnClickedCopyrgb()
{
	CopyWithFormat(L"RGB(%d, %d, %d)");
}

void CColorMajestyDlg::OnAdd2View()
{
	ColorInfo color_info;

	if (!m_cColorList.GetSelectedColorInfo(color_info))
		return;

	ColorManager.Add2Preview(color_info);
	m_cPreviewWnd.Invalidate(TRUE);
}


void CColorMajestyDlg::OnBnClickedCopyhex()
{
	CopyWithFormat(L"#%02X%02X%02X");
}

HBRUSH CColorMajestyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
		case IDC_COPY_SUCCESS:
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(0, 0, 200));
			return CreateSolidBrush(RGB(255, 255, 170));
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CColorMajestyDlg::CopyWithFormat(LPCWSTR lpFormat)
{
	ColorInfo color_info;

	if (!m_cColorList.GetSelectedColorInfo(color_info))
		return;

	CString strColor;
	strColor.Format(lpFormat,
		GetRValue(color_info.Color), GetGValue(color_info.Color), GetBValue(color_info.Color));

	CWnd* pCopyResultWnd = GetDlgItem(IDC_COPY_SUCCESS);

	if (CopyToClipboard(strColor.GetString()))
	{
		pCopyResultWnd->SetWindowText(L"Successfully copied:\n" + strColor);
	}
	else
	{
		pCopyResultWnd->SetWindowText(L"Failed to Copy.");
	}

	pCopyResultWnd->ShowWindow(SW_SHOW);

	// Hide the success indicator after 2 secs
	SetTimer(0xA55, 4000, nullptr);
}


void CColorMajestyDlg::OnRclickColorDisp(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem == LB_ERR)
	{
		return;
	}

	m_cColorList.ClientToScreen(&pNMItemActivate->ptAction);

	m_cColorListContextMenu.TrackPopupMenu(TPM_LEFTBUTTON, pNMItemActivate->ptAction.x,
		pNMItemActivate->ptAction.y, this);

	*pResult = 0;
}

void CColorMajestyDlg::CreateContextMenus()
{
	m_cColorListContextMenu.CreatePopupMenu();

	m_cColorListContextMenu.AppendMenu(MF_STRING, IDC_VIEWFULL, L"View Fullscreen");
	m_cColorListContextMenu.AppendMenu(MF_STRING, IDC_ADD2VIEW, L"Add Color to View");
	m_cColorListContextMenu.AppendMenu(MF_SEPARATOR);
	m_cColorListContextMenu.AppendMenu(MF_STRING, IDC_COPYRGB, L"Copy as RGB");
	m_cColorListContextMenu.AppendMenu(MF_STRING, IDC_COPYHEX, L"Copy as HexCode");

	m_cColorListContextMenu.SetDefaultItem(IDC_VIEWFULL);
}

void CColorMajestyDlg::OnNMClickAdd2view(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);

	OnAdd2View();

	*pResult = 0;
}