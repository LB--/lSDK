#include "Common.hpp"

#include <fstream>

int MMF2Func CreateObject(mv *mV, LO *lo, SerializedED *SED)
{	DST();
	DM("CreateObject(ppp", "mV", mV, "lo", lo, "SED", SED);
	MessageBox(mV->mvHEditWin, _T("Use \"Create From File\" in the new object dialog, and select your Widget Definition File."), _T("Widget+"), MB_OK|MB_ICONERROR);
	return 1;
}
BOOL MMF2Func UsesFile(mv *mV, LPTSTR Filename)
{	DST();
	DM("UsesFile(pt", "mV", mV, "Filename", Filename);
	TCHAR FileExtension[_MAX_EXT];
	_tsplitpath(Filename, NULL, NULL, NULL, FileExtension);
	if(std::basic_string<TCHAR>(FileExtension) == _T(".wdf"))
	{
		std::ifstream def (lSDK::EnsureNarrow(Filename).c_str());
		json_verifier jv (def);
		if(jv.json)
		{
			return TRUE;
		}
		else
		{
			MessageBoxA
			(
				mV->mvHEditWin,
				(std::string("Error while loading \"")+lSDK::EnsureNarrow(Filename)+"\":\r\n"+jv.error).c_str(),
				"Widget+",
				MB_OK|MB_ICONERROR
			);
			return FALSE;
		}
	}
	return FALSE;
}
void MMF2Func CreateFromFile(mv *mV, LPTSTR Filename, SerializedED *SED)
{	DST();
	DM("CreateFromFile(ptp", "mV", mV, "Filename", Filename, "SED", SED);
	std::fstream def (lSDK::EnsureNarrow(Filename).c_str());
	ED(std::string((std::istreambuf_iterator<char>(def)), std::istreambuf_iterator<char>())).Serialize(mV, SED);
}
void MMF2Func PutObject(mv *mV, LO *lo, SerializedED *SED, unsigned short othersame)
{	DST();
	DM("PutObject(pppi", "mV", mV, "lo", lo, "SED", SED, "othersame", int(othersame));
}
void MMF2Func DuplicateObject/*CloneObject*/(mv *mV, OI *oi, SerializedED *SED)
{	DST();
	DM("DuplicateObject(ppp", "mV", mV, "oi", oi, "SED", SED);
}
void MMF2Func RemoveObject(mv *mV, LO *lo, SerializedED *SED, unsigned short othersame)
{	DST();
	DM("RemoveObject(pppi", "mV", mV, "lo", lo, "SED", SED, "othersame", int(othersame));
}

BOOL MMF2Func EditObject(mv *mV, OI *oi, LO *lo, SerializedED *SED)
{	DST();
	DM("EditObject(pppp", "mV", mV, "oi", oi, "lo", lo, "SED", SED);
	//mV->mvEditAnimation();
	return TRUE;
}

BOOL MMF2Func SetEditSize(mv *mV, SerializedED *SED, int X, int Y)
{	DST();
	DM("SetEditSize(ppii", "mV", mV, "SED", SED, "X", X, "Y", Y);
	return TRUE;
}
void MMF2Func GetObjectRect(mv *mV, RECT *rect, LO *lo, SerializedED *SED)
{//	DST();
//	DM("GetObjectRect(pppp", "mV", mV, "rect", rect, "lo", lo, "SED", SED);
	rect->right = rect->left + 32;//w
	rect->bottom = rect->top + 32;//h
}

int MMF2Func MakeIconEx(mv *mV, cSurface *Icon, LPTSTR Name, OI *oi, SerializedED *SED)
{	DST();
	DM("MakeIconEx(ppppp", "mV", mV, "Icon", Icon, "Name", Name, "oi", oi, "SED", SED);
	return Icon->LoadImage(DLL, EXO_ICON) != 0;
}
void MMF2Func EditorDisplay(mv *mV, OI *oi, LO *lo, SerializedED *SED, RECT *Clip)
{	DST();
	DM("EditorDisplay(ppppp", "mV", mV, "oi", oi, "lo", lo, "SED", SED, "Clip", Clip);
	cSurface *Frame = WinGetSurface((int)mV->mvIdEditWin);
	if(!Frame) return;
	cSurface Obj;
	Obj.Create(32, 32, Frame);
	Obj.LoadImage(DLL, EXO_ICON, LI_REMAP);
	Obj.Blit(*Frame, Clip->left, Clip->top, BMODE_TRANSP, BOP_COPY, 0);
}

extern"C" BOOL MMF2Func IsTransparent(mv *mV, OI *lo, SerializedED *SED, int X, int Y)
{//	DST();
//	DM("IsTransparent(pppii", "mV", mV, "lo", lo, "SED", SED, "X", X, "Y", Y);
	return FALSE;
}

void MMF2Func PrepareToWriteObject(mv *mV, SerializedED *SED, OI *oi)
{	DST();
	DM("PrepareToWriteObject(ppp", "mV", mV, "SED", SED, "oi", oi);
}

BOOL MMF2Func GetFilters(mv *mV, SerializedED *SED, DWORD Flags, LPVOID)
{	DST();
	DM("GetFilters(ppi", "mV", mV, "SED", SED, "Flags", Flags);
	return FALSE;
}

void MMF2Func PrepareFlexBuild(mv *mV, SerializedED *SED, LPCWSTR TempFolder)
{	DST();
	DM("PrepareFlexBuild(ppu", "mV", mV, "SED", SED, "TempFolder", TempFolder);
}
