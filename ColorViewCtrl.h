#pragma once


#define SQUARE_SIZE		68
#define SQUARE_MARGIN	4

// CColorViewCtrl

class CColorViewCtrl : public CListCtrl
{
	ColorInfoVector Items;

	CFont m_fNameFont;
		 
public:
	CColorViewCtrl();
	virtual ~CColorViewCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	void MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct );
	LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);

	bool GetSelectedColorInfo(ColorInfo&) const;

	void InsertItem(const ColorInfo&);
	void Clear();
};


