#pragma once

#include <vector>

struct ColorInfo
{
	DWORD Color;
	CString ColorName;
};

typedef std::vector<ColorInfo> ColorInfoVector;
class CColorManager
{
	ColorInfoVector Colors;
	std::vector<ColorInfoVector::const_iterator> ResultVector;
	std::vector<ColorInfoVector::const_iterator>::const_iterator LastResult;

	ColorInfoVector Colors2Preview;

public:
	static COLORREF HexToColor(LPCSTR);

	CColorManager(void);
	~CColorManager(void);
	bool LoadColors();
	bool BeginSearch( const CString& strInput );
	bool FindNext();
	const ColorInfo& GetNext();

	void Add2Preview(const ColorInfo&);
	const ColorInfoVector* GetPreviewVector() const;
};

