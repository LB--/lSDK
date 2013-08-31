#include "Common.hpp"

unsigned short MMF2Func GetRunObjectDataSize(RunHeader *rh, SerializedED *SED)
{
	DM("GetRunObjectDataSize(pp", "rh", rh, "SED", SED);
	return sizeof(RD);
}

short MMF2Func CreateRunObject(RD *rd, SerializedED *SED, createObjectInfo *COI)
{
	DM("CreateRunObject(ppp", "rd", rd, "SED", SED, "COI", COI);
	return 0;
}
short MMF2Func DestroyRunObject(RD *rd, long fast)
{
	DM("DestroyRunObject(pi", "rd", rd, "fast", fast);
	return 0;
}

short MMF2Func HandleRunObject(RD *rd)
{
	DM("HandleRunObject(p", "rd", rd);
	return REFLAG_ONESHOT;
}
short MMF2Func DisplayRunObject(RD *rd)
{
	DM("DisplayRunObject(p", "rd", rd);
	return 0;
}

cSurface *MMF2Func GetRunObjectSurface(RD *rd)
{
	DM("GetRunObjectSurface(p", "rd", rd);
	return NULL;
}
LPSMASK MMF2Func GetRunObjectCollisionMask(RD *rd, LPARAM lParam)
{
	DM("GetRunObjectCollisionMask(pi", "rd", rd, "lParam", lParam);
	return NULL;
}

short MMF2Func SaveBackground(RD *rd)
{
	DM("SaveBackground(p", "rd", rd);
	return 0;
}
short MMF2Func RestoreBackground(RD *rd)
{
	DM("RestoreBackground(p", "rd", rd);
	return 0;
}
short MMF2Func KillBackground(RD *rd)
{
	DM("KillBackground(p", "rd", rd);
	return 0;
}

short MMF2Func PauseRunObject(RD *rd)
{
	DM("PauseRunObject(p", "rd", rd);
	return 0;
}
short MMF2Func ContinueRunObject(RD *rd)
{
	DM("ContinueRunObject(p", "rd", rd);
	return 0;
}

BOOL MMF2Func SaveRunObject(RD *rd, HANDLE File)
{
	DM("SaveRunObject(pp", "rd", rd, "File", File);
	return TRUE;
}
BOOL MMF2Func LoadRunObject(RD *rd, HANDLE File)
{
	DM("LoadRunObject(pp", "rd", rd, "File", File);
	return TRUE;
}

void MMF2Func StartApp(mv *mV, CRunApp *App)
{
	DM("StartApp(pp", "mV", mV, "App", App);
}
void MMF2Func EndApp(mv *mV, CRunApp *App)
{
	DM("EndApp(pp", "mV", mV, "App", App);
}

void MMF2Func StartFrame(mv *mV, CRunApp *App, int FrameIndex)
{
	DM("StartFrame(ppi", "mV", mV, "App", App, "FrameIndex", FrameIndex);
}
void MMF2Func EndFrame(mv *mV, CRunApp *App, int FrameIndex)
{
	DM("EndFrame(ppi", "mV", mV, "App", App, "FrameIndex", FrameIndex);
}

LRESULT CALLBACK WindowProc(RunHeader *rh, HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
{
	DM("WindowProc(ppiii", "rh", rh, "Window", Window, "Message", Message, "wParam", wParam, "lParam", lParam);
	return 0;
}
