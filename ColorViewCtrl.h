#pragma once

constexpr auto SQUARE_SIZE = 68;
constexpr auto SQUARE_MARGIN = 4;

class CColorViewCtrl : public CListCtrl
{
	ColorInfoVector Items;
	CFont m_fNameFont;		 

public:
	CColorViewCtrl();

public:
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);

	bool GetSelectedColorInfo(ColorInfo&) const;
	void InsertItem(const ColorInfo&);
	void Clear();

protected:
	DECLARE_MESSAGE_MAP()
};


