
// Color MajestyDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "colorviewctrl.h"
#include "FullscreenWnd.h"

using CWndResizer = CWnd;

// CColorMajestyDlg dialog
class CColorMajestyDlg : public CDialog
{
	CWndResizer m_cWndResizer;

	CColorManager& ColorManager;
public:
	CColorMajestyDlg();

// Dialog Data
	enum { IDD = IDD_COLORMAJESTY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_cColorInput;
	afx_msg void OnEnChangeColorin();
	CColorViewCtrl m_cColorList;
	CMenu m_cColorListContextMenu;
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedCopyrgb();
	afx_msg void OnBnClickedCopyhex();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void CopyWithFormat( LPCWSTR param1 );
	afx_msg void OnRclickColorDisp(NMHDR *pNMHDR, LRESULT *pResult);
	void CreateContextMenus();
	
	
	CPreviewWnd m_cPreviewWnd;
	afx_msg void OnNMClickAdd2view(NMHDR *pNMHDR, LRESULT *pResult);
	void OnAdd2View();
};
