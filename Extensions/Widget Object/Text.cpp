#include "Common.hpp"

/*Edittime*/

DWORD MMF2Func GetTextCaps(mv *mV, SerializedED *SED)
{
//	DM("GetTextCaps(pp", "mV", mV, "SED", SED);
	return 0;
}

BOOL MMF2Func GetTextFont(mv *mV, SerializedED *SED, LPLOGFONT plf, LPTSTR, UINT)
{
//	DM("GetTextFont(ppp", "mV", mV, "SED", SED, "plf", plf);
	return TRUE;
}
BOOL MMF2Func SetTextFont(mv *mV, SerializedED *SED, LPLOGFONT plf, LPCSTR)
{
//	DM("SetTextFont(ppp", "mV", mV, "SED", SED, "plf", plf);
	return TRUE;
}

COLORREF MMF2Func GetTextClr(mv *mV, SerializedED *SED)
{
//	DM("GetTextClr(pp", "mV", mV, "SED", SED);
	return 0;
}
void MMF2Func SetTextClr(mv *mV, SerializedED *SED, COLORREF Color)
{
//	DM("SetTextClr(ppi", "mV", mV, "SED", SED, "Color", Color);
}

DWORD MMF2Func GetTextAlignment(mv *mV, SerializedED *SED)
{
//	DM("GetTextAlignment(pp", "mV", mV, "SED", SED);
	return 0;
}
void MMF2Func SetTextAlignment(mv *mV, SerializedED *SED, DWORD AlignFlags)
{
//	DM("SetTextAlignment(ppi", "mV", mV, "SED", SED, "AlignFlags", AlignFlags);
}

/*Runtime*/

void MMF2Func GetRunObjectFont(RD *rd, LOGFONT *plf)
{
//	DM("GetRunObjectFont(pp", "rd", rd, "plf", plf);
}
void MMF2Func SetRunObjectFont(RD *rd, LOGFONT *plf, RECT *Rect)
{
//	DM("SetRunObjectFont(ppp", "rd", rd, "plf", plf, "Rect", Rect);
}

COLORREF MMF2Func GetRunObjectTextColor(RD *rd)
{
//	DM("GetRunObjectTextColor(p", "rd", rd);
	return 0;
}
void MMF2Func SetRunObjectTextColor(RD *rd, COLORREF Color)
{
//	DM("SetRunObjectTextColor(pi", "rd", rd, "Color", Color);
}
