#include "StdAfx.h"
#include "ColorManager.h"
#include "resource.h"
#include <algorithm>

#define ITEM_SEPARATOR	L','

CColorManager::CColorManager(void)
{
}


CColorManager::~CColorManager(void)
{
}

#define GetNibble(_x)	\
	( ((_x) > '9') ? ( (_x) - 55 ) : ((_x) - 48 ) )

/*COLORREF CColorManager::HexToColor( LPCSTR lpszInput)
{
//	LPCCH pChar = lpszInput;
	/*CHAR cChar;

	DWORD nResult = 0;
	BYTE nValue;

	// Input string is exactly 6-characters long:
	// First 2: Green
	// Second 2: Blue
	// Third 2: Red

	BYTE Codes[3];
	*/

	
			/*

		_ASSERTE((cChar >='0' && cChar<='9') || (cChar>='A' && cChar<='F'));

		if (cChar >='0' && cChar <='9')
		{
			nValue = cChar - '0';
		}
		else
		{	
			nValue = cChar - 'A' + 10;
		}

		nResult = (nResult << 4) + nValue;

		lpszInput++;

//	} //while (pChar>=lpszInput);

	return nResult;*
}*/

bool CColorManager::LoadColors()
{
	HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(IDR_COLORCODES),  L"COLORCODES");

	if(!hResource)
		return false;

	HGLOBAL hResHandle = LoadResource(NULL, hResource);

	if(!hResHandle)
	{
		FreeResource(hResource);
		return false;
	}

	// Resource is ANSII (as yet)
	const char* lpData = static_cast<char*> ( LockResource(hResHandle) );

	if(!lpData)
	{
		FreeResource(hResource);
		return false;
	}

	CStringA strColorsString;

	// For prefixing
	LPCTSTR Zeroes = L"00000";
	LPCSTR pInput;

	strColorsString.SetString(lpData, SizeofResource(NULL, hResource));

	// A basic assert.. might be useful in future.
	ASSERT ( SizeofResource(NULL, hResource) == strColorsString.GetLength() );

	FreeResource(hResource);

	// CStdioFile m_cFile;

	// m_cFile.Open(L"names.csv", CFile::modeRead | CFile::typeText);

	CString strOneLine;

	CString  strName;
	CString strColor;
	CStringA strColorA;

	ColorInfo color_info;

	int nIndex;


	int nFindAt = 0;
	int nFountAt;
	do
	{
		nFountAt = strColorsString.Find(L'\n', nFindAt);

		if ( nFountAt == -1)
			break;

		strOneLine = strColorsString.Mid(nFindAt, nFountAt - nFindAt - 1);

		// For next search
		nFindAt = nFountAt+1;

		nIndex = strOneLine.Find(ITEM_SEPARATOR);

		// Separator not found, or line seems to be invalid.
		if ( nIndex <= 0 )
		{
			ASSERT(FALSE);
			continue;
		}

		ASSERT(nIndex > 0);

		strColor = strOneLine.Left(nIndex);

		// The rest is meaning
		strName = strOneLine.Mid(nIndex+1);
		
		color_info.ColorName= ((TCHAR)toupper(strName[0])) + strName.Mid(1);
		

		
		ASSERT(strColor.GetLength() > 0);

		if (strColor.GetLength() < 6)
		{			
			 strColor = (Zeroes + strColor.GetLength() -1 ) + strColor;
		}
		// Must be exactly six-chars
		ASSERT(strColor.GetLength() == 6);

		strColorA = strColor.MakeUpper();
		pInput = strColorA;

		color_info.Color= RGB((GetNibble(pInput[0]) << 4) + GetNibble(pInput[1]),
			(GetNibble(pInput[2]) << 4) + GetNibble(pInput[3]),
			(GetNibble(pInput[4]) << 4) + GetNibble(pInput[5]));

			//HexToColor(CStringA(strColor).MakeUpper());		

		ASSERT( color_info.Color >=0 && color_info.Color<=RGB(255,255,255));

		Colors.push_back(color_info);

	} while(true);


	// Free up memory!
	strColorsString.Empty();

#ifdef _DEBUG
	// for_each()
#endif

	return true;
}

bool CColorManager::BeginSearch( const CString& strInput )
{
	ResultVector.clear();

	CString lcInput = strInput;
	lcInput.MakeUpper();

	CString lcColor;

	//using namespace std;
	for (auto iter = Colors.cbegin(); iter != Colors.cend(); ++iter)
	{
		lcColor = iter->ColorName;
		lcColor.MakeUpper();
		if (lcColor.Find(lcInput)>=0)
		{
			ResultVector.push_back(iter);
		}				
	}

	LastResult = ResultVector.cbegin();
	

	return true;
}

bool CColorManager::FindNext()
{
	if (LastResult == ResultVector.cend())
	{
		return false;
	}

	return true;	
}

const ColorInfo& CColorManager::GetNext()
{
	return **(LastResult++);
}

void CColorManager::Add2Preview( const ColorInfo& lcColorInfo)
{
	Colors2Preview.push_back(lcColorInfo);
}

const ColorInfoVector* CColorManager::GetPreviewVector() const
{
	return &Colors2Preview;
}
