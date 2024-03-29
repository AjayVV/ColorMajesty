#include "stdafx.h"
#include "Color Majesty.h"
#include "ColorViewCtrl.h"

CColorViewCtrl::CColorViewCtrl()
{
	m_fNameFont.CreateFont(22, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
}

BEGIN_MESSAGE_MAP(CColorViewCtrl, CListCtrl)
	ON_WM_MEASUREITEM_REFLECT()
	ON_MESSAGE(WM_SETFONT, OnSetFont)
END_MESSAGE_MAP()

void CColorViewCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	if (/*(lpDrawItemStruct->itemAction | ODA_SELECT) &&*/
		(lpDrawItemStruct->itemState & ODS_SELECTED))
	{
		//DrawGradient(pDC, lpDrawItemStruct->rcItem);		
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem, RGB(222, 224, 222));

	}
	else
	{
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_WINDOW));
		//pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
	}

	pDC->SetBkMode(TRANSPARENT);
	ColorInfo& color_info = Items[lpDrawItemStruct->itemData];

	lpDrawItemStruct->rcItem.left += 10;


	RECT rect = lpDrawItemStruct->rcItem;
	rect.top += SQUARE_MARGIN;
	rect.bottom -= SQUARE_MARGIN;
	rect.left += SQUARE_MARGIN;
	rect.right = rect.left + SQUARE_SIZE;
	pDC->FillSolidRect(&rect, color_info.Color);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(&rect);



	CString strRGB;
	rect.left = rect.right + 20;
	rect.right = rect.left + 220;

	pDC->SetTextColor(RGB(158, 116, 27));	
	CFont *pOldFont = pDC->SelectObject(&m_fNameFont);
	pDC->DrawText(color_info.ColorName, &rect, DT_LEFT | DT_SINGLELINE);

	pDC->SelectObject(pOldFont);


	rect.top += 20;

	strRGB.Format(L"RGB(%d, %d, %d)",
		GetRValue(color_info.Color), GetGValue(color_info.Color), GetBValue(color_info.Color));

	pDC->SetTextColor(RGB(64, 64, 64));
	pDC->DrawText(strRGB, &rect, DT_SINGLELINE);;

	rect.top += 15;

	strRGB.Format(L"%d%%, %d%%, %d%%",
		static_cast<int>(GetRValue(color_info.Color) / 2.55),
		static_cast<int>(GetGValue(color_info.Color) / 2.55),
		static_cast<int>(GetBValue(color_info.Color) / 2.55));

	pDC->DrawText(strRGB, &rect, DT_SINGLELINE);;

	rect.top += 15;

	strRGB.Format(L"#%02X%02X%02X", GetRValue(color_info.Color), GetGValue(color_info.Color), GetBValue(color_info.Color));
	pDC->DrawText(strRGB, &rect, DT_SINGLELINE);;
}


void CColorViewCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	UNREFERENCED_PARAMETER(lpMeasureItemStruct);

	// TODO: Add your message handler code here and/or call default

	//	CListCtrl::MeasureItem(nIDCtl, lpMeasureItemStruct);
}

LRESULT CColorViewCtrl::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	CRect rc;
	GetWindowRect(&rc);

	WINDOWPOS wp;
	wp.hwnd = this->m_hWnd;
	wp.cx = rc.Width();
	wp.cy = rc.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;

	LRESULT lrReturn(Default());

	SendMessage(WM_WINDOWPOSCHANGED, 0, reinterpret_cast<LPARAM> (&wp));

	return lrReturn;
}


void CColorViewCtrl::InsertItem(const ColorInfo& lcColorInfo)
{
	Items.push_back(lcColorInfo);

	const auto nItemCount = GetItemCount();

	__super::InsertItem(nItemCount, L"");
	SetItemData(nItemCount, Items.size() - 1);
}

bool CColorViewCtrl::GetSelectedColorInfo(ColorInfo& lcColorInfo) const
{
	if (GetSelectedCount() == 0)
	{
		ASSERT(false);
		return false;
	}

	POSITION pos = GetFirstSelectedItemPosition();

	lcColorInfo = Items[GetNextSelectedItem(pos)];

	return true;
}

void CColorViewCtrl::Clear()
{
	DeleteAllItems();
	Items.clear();
}
