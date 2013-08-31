#include "Common.hpp"

int MMF2Func CreateObject(mv *mV, LO *lo, SerializedED *SED)
{
	DM("CreateObject(ppp", "mV", mV, "lo", lo, "SED", SED);
	MessageBox(mV->mvHEditWin, _T("Use \"Create From File\" in the new object dialog, and select your Widget Definition File."), _T("Widget+"), MB_OK|MB_ICONERROR);
	return 1;
}
BOOL MMF2Func UsesFile(mv *mV, LPTSTR Filename)
{
	DM("UsesFile(ps", "mV", mV, "Filename", Filename);
	TCHAR FileExtension[_MAX_EXT];
	_tsplitpath(Filename, NULL, NULL, NULL, FileExtension);
	return stdstring(FileExtension) == ".wdf" ? TRUE : FALSE;
}
void MMF2Func CreateFromFile(mv *mV, LPTSTR Filename, SerializedED *SED)
{
	DM("CreateFromFile(psp", "mV", mV, "Filename", Filename, "SED", SED);
}
void MMF2Func PutObject(mv *mV, LO *lo, SerializedED *SED, unsigned short othersame)
{
	DM("PutObject(pppi", "mV", mV, "lo", lo, "SED", SED, "othersame", int(othersame));
}
void MMF2Func DuplicateObject/*CloneObject*/(mv *mV, OI *oi, SerializedED *SED)
{
	DM("DuplicateObject(ppp", "mV", mV, "oi", oi, "SED", SED);
}
void MMF2Func RemoveObject(mv *mV, LO *lo, SerializedED *SED, unsigned short othersame)
{
	DM("RemoveObject(pppi", "mV", mV, "lo", lo, "SED", SED, "othersame", int(othersame));
}

BOOL MMF2Func EditObject(mv *mV, OI *oi, LO *lo, SerializedED *SED)
{
	DM("EditObject(pppp", "mV", mV, "oi", oi, "lo", lo, "SED", SED);
	//mV->mvEditAnimation();
	return TRUE;
}

BOOL MMF2Func SetEditSize(mv *mV, SerializedED *SED, int X, int Y)
{
	DM("SetEditSize(ppii", "mV", mV, "SED", SED, "X", X, "Y", Y);
	return TRUE;
}
void MMF2Func GetObjectRect(mv *mV, RECT *rect, LO *lo, SerializedED *SED)
{
//	DM("GetObjectRect(pppp", "mV", mV, "rect", rect, "lo", lo, "SED", SED);
	rect->right = rect->left + 32;//w
	rect->bottom = rect->top + 32;//h
}

int MMF2Func MakeIconEx(mv *mV, cSurface *Icon, LPTSTR Name, OI *oi, SerializedED *SED)
{
	DM("MakeIconEx(ppppp", "mV", mV, "Icon", Icon, "Name", Name, "oi", oi, "SED", SED);
	return Icon->LoadImage(DLL, EXO_ICON) != 0;
}
void MMF2Func EditorDisplay(mv *mV, OI *oi, LO *lo, SerializedED *SED, RECT *Clip)
{
	DM("EditorDisplay(ppppp", "mV", mV, "oi", oi, "lo", lo, "SED", SED, "Clip", Clip);
	cSurface *Frame = WinGetSurface((int)mV->mvIdEditWin);
	if(!Frame) return;
	cSurface Obj;
	Obj.Create(32, 32, Frame);
	Obj.LoadImage(DLL, EXO_ICON, LI_REMAP);
	Obj.Blit(*Frame, Clip->left, Clip->top, BMODE_TRANSP, BOP_COPY, 0);
}

extern"C" BOOL MMF2Func IsTransparent(mv *mV, OI *lo, SerializedED *SED, int X, int Y)
{
//	DM("IsTransparent(pppii", "mV", mV, "lo", lo, "SED", SED, "X", X, "Y", Y);
	return FALSE;
}

void MMF2Func PrepareToWriteObject(mv *mV, SerializedED *SED, OI *oi)
{
	DM("PrepareToWriteObject(ppp", "mV", mV, "SED", SED, "oi", oi);
}

BOOL MMF2Func GetFilters(mv *mV, SerializedED *SED, DWORD Flags, LPVOID)
{
	DM("GetFilters(ppi", "mV", mV, "SED", SED, "Flags", Flags);
	return FALSE;
}

void MMF2Func PrepareFlexBuild(mv *mV, SerializedED *SED, LPCWSTR TempFolder)
{
	DM("PrepareFlexBuild(pp", "mV", mV, "SED", SED);
}
