#pragma once

struct ColorInfo
{
	DWORD Color;
	CString ColorName;
};

using ColorInfoVector = std::vector<ColorInfo>;

class CColorManager
{
	ColorInfoVector Colors;
	std::vector<ColorInfoVector::const_iterator> ResultVector;
	std::vector<ColorInfoVector::const_iterator>::const_iterator LastResult;

	ColorInfoVector Colors2Preview;

public:
	bool LoadColors();
	bool BeginSearch(const CString& strInput);
	bool FindNext();
	const ColorInfo& GetNext();

	void Add2Preview(const ColorInfo&);
	const ColorInfoVector* GetPreviewVector() const;
};

