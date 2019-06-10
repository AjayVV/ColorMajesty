// FullscreenWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Color Majesty.h"
#include "FullscreenWnd.h"
#include <algorithm>


/************************************************************************/
/*              CPreviewWnd												*/
/************************************************************************/

BEGIN_MESSAGE_MAP(CPreviewWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CPreviewWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	RenderRectangles(this, dc);
}

void RenderRectangles(CWnd* pWnd, CDC& dc)
{
	CColorManager& ColorManager = GetColorManager();

	const ColorInfoVector* pColorVector = ColorManager.GetPreviewVector();

	CBrush theBrush;
	HBRUSH hOldBrush;

	RECT clientRect;	
	pWnd->GetClientRect(&clientRect);

	RECT tempRect(clientRect);

	std::vector<RECT> RectVector;

	float nVertDiv, nHortDiv;

	switch(pColorVector->size())
	{
	case 0:
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(122,0,100));
		dc.DrawText(L"Double click any color to view in Full Screen.\n\nYou can also add up to 8 colors this To-View", &clientRect, DT_WORDBREAK);
		return;

	case 1:
		RectVector.push_back(clientRect);
		break;

	case 2:		
		tempRect.right = clientRect.right/2;
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = clientRect.right;
		RectVector.push_back(tempRect);
		break;
		
	case 3:
		nVertDiv = clientRect.right/3.0f;

		tempRect.right = (LONG)(clientRect.left+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = (LONG)(tempRect.left+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = clientRect.right;	// Must extend!
		RectVector.push_back(tempRect);
		break;

	case 4:
		nVertDiv = clientRect.right/2.0f;
		nHortDiv = clientRect.bottom/2.0f;

		// TL
		tempRect.right = (LONG)(clientRect.left+nVertDiv);
		tempRect.bottom = (LONG)(clientRect.top+nHortDiv);
		RectVector.push_back(tempRect);

		// TR
		tempRect.left = tempRect.right;
		tempRect.right = clientRect.right;
		RectVector.push_back(tempRect);

		// BL
		tempRect.top  = (LONG)(clientRect.top + nHortDiv);
		tempRect.left = clientRect.left;		
		tempRect.right = (LONG)(clientRect.left+nVertDiv);
		tempRect.bottom = clientRect.bottom;
		RectVector.push_back(tempRect);

		// BR
		tempRect.left = tempRect.right;
		tempRect.right = clientRect.right;
		RectVector.push_back(tempRect);
		break;

	case 5:

		tempRect.right = (LONG)(clientRect.right/2.0);
		tempRect.bottom= (LONG)(clientRect.bottom/2.0);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = clientRect.right;
		RectVector.push_back(tempRect);


		nVertDiv = clientRect.right/3.0f;
		tempRect.top = (LONG)(clientRect.bottom/2.0f);

		tempRect.left = clientRect.left;
		tempRect.bottom  = clientRect.bottom;
		tempRect.right = (LONG)(clientRect.left+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = (LONG)(tempRect.left+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = clientRect.right;	// Must extend!
		RectVector.push_back(tempRect);
		break;

	case 6:

		nVertDiv = clientRect.right/3.0f;

		//tempRect.top = (LONG)(clientRect.top);

		tempRect.left = clientRect.left;
		tempRect.bottom  = (LONG)(clientRect.bottom/2.0f);
		tempRect.right = (LONG)(clientRect.left+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = static_cast<LONG>( tempRect.right+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = clientRect.right;
		RectVector.push_back(tempRect);
		
		tempRect.top = (LONG)(clientRect.bottom/2.0f);

		tempRect.left = clientRect.left;
		tempRect.bottom  = clientRect.bottom;
		tempRect.right = (LONG)(clientRect.left+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = (LONG)(tempRect.left+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = clientRect.right;	// Must extend!
		RectVector.push_back(tempRect);
		break;

	case 7:
		nVertDiv = clientRect.right/3.0f;

		//tempRect.top = (LONG)(clientRect.top);

		tempRect.left = clientRect.left;
		tempRect.bottom  = (LONG)(clientRect.bottom/2.0f);
		tempRect.right = (LONG)(clientRect.left+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = static_cast<LONG>(tempRect.right+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = clientRect.right;
		RectVector.push_back(tempRect);

		nVertDiv = clientRect.right/4.0f;

		tempRect.top = static_cast<LONG>(clientRect.bottom/2.0f);
		
		tempRect.left = clientRect.left;
		tempRect.bottom  = (LONG)(clientRect.bottom);
		tempRect.right = (LONG)(clientRect.left+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = static_cast<LONG>(tempRect.right+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = static_cast<LONG>(tempRect.right+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = clientRect.right;
		RectVector.push_back(tempRect);
		break;

	case 8:

		nVertDiv = clientRect.right/4.0f;

		//tempRect.top = (LONG)(clientRect.top);

		tempRect.left = clientRect.left;
		tempRect.bottom  = (LONG)(clientRect.bottom/2.0f);
		tempRect.right = (LONG)(clientRect.left+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = static_cast<LONG>(tempRect.right+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = static_cast<LONG>(tempRect.right+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = clientRect.right;
		RectVector.push_back(tempRect);

		nVertDiv = clientRect.right/4.0f;

		tempRect.top = static_cast<LONG>(clientRect.bottom/2.0f);

		tempRect.left = clientRect.left;
		tempRect.bottom  = (LONG)(clientRect.bottom);
		tempRect.right = (LONG)(clientRect.left+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = static_cast<LONG>(tempRect.right+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = static_cast<LONG>(tempRect.right+nVertDiv);
		RectVector.push_back(tempRect);

		tempRect.left  = tempRect.right;
		tempRect.right = clientRect.right;
		RectVector.push_back(tempRect);

	}

	int nIndex = 0;

	std::for_each(RectVector.cbegin(), RectVector.cend(), [&](const RECT& rect)
	{
		theBrush.CreateSolidBrush(pColorVector->at(nIndex++).Color);

		hOldBrush = (HBRUSH)dc.SelectObject(theBrush);

		dc.FillRect(&rect,&theBrush);

		dc.SelectObject(hOldBrush);
		theBrush.DeleteObject();
	});
}

