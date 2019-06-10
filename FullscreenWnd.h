#pragma once


// CFullscreenWnd

void RenderRectangles(CWnd* pWnd, CDC& dc);

class CPreviewWnd : public CWnd
{	
public:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnPaint();
};
