#include "Common.hpp"

#include <fstream>
#include <ctime>
#include <algorithm>

HINSTANCE DLL = 0;
BOOL WINAPI DllMain(HINSTANCE Dll, DWORD Reason, LPVOID lpReserved)
{
	switch(Reason)
	{
	case DLL_PROCESS_ATTACH:
		{
			DLL = Dll;
			DM("DLL process attaching(p", "lpReserved", lpReserved);
		} break;
	case DLL_PROCESS_DETACH:
		{
			DM("DLL process detaching(p", "lpReserved", lpReserved);
		} break;
	case DLL_THREAD_ATTACH:
		{
			DM("DLL thread attaching(p", "lpReserved", lpReserved);
		} break;
	case DLL_THREAD_DETACH:
		{
			DM("DLL thread detaching(p", "lpReserved", lpReserved);
		} break;
	}
	return TRUE;
}

#ifdef DEBUG
struct GlobalLifetimeDebug
{
	GlobalLifetimeDebug()
	{
		DebugLog("constructing globals(i", "Widget+ Object Version", ExtensionVersionNumber);
	}
	~GlobalLifetimeDebug()
	{
		DebugLog("destructing globals(");
		DebugLog("\n================================================================\n");
	}
}gld;
void DebugLog(char const *func, ...)
{
	std::basic_ofstream<wchar_t> dbo ("/Widget_Debug.txt", std::ios_base::out|std::ios_base::ate|std::ios_base::app);

	std::string f (func);
	if(f.find('(') != std::string::npos)
	{
		dbo << lSDK::EnsureWide(f.substr(0, f.find('('))) << L" (DLL = 0x" << (void *)DLL << L")" << std::endl;
		f = f.substr(f.find('(')+1);

		va_list vars;
		va_start(vars, func);
		for(std::string::const_iterator it = f.begin(); it != f.end(); ++it)
		{
			dbo << L'\t' << lSDK::EnsureWide(va_arg(vars, char const *)) << " = ";
			switch(*it)
			{
			case 'p': dbo << L"0x"    <<                  va_arg(vars, void *);                    break;
			case 'i': dbo <<                              va_arg(vars, int);                       break;
			case 's': dbo << L'"'     << lSDK::EnsureWide(va_arg(vars, char const *))   << L'"';   break;
			case 'u': dbo << L"L\""   <<                  va_arg(vars, wchar_t const *) << L'"';   break;
			case 't': dbo << L"_T(\"" << lSDK::EnsureWide(va_arg(vars, TCHAR const *))  << L"\")"; break;
			}
			dbo << std::endl;
		}
		va_end(vars);
	}
	else
	{
		dbo << lSDK::EnsureWide(f) << std::endl;
	}
}
#endif

int MMF2Func InitExt(mv *mV, int Quiet)
{	DST();
	DM("InitExt(pi", "mV", mV, "Quiet", Quiet);
	TCHAR buffer[_MAX_PATH];
	if(GetModuleFileName(DLL, buffer, _MAX_PATH))
	{
		DM("Current MFX(t", "", buffer);
	}
	return 0;
}
int MMF2Func FreeExt(mv *mV)
{	DST();
	DM("FreeExt(p", "mV", mV);
	return 0;
}

void MMF2Func GetSubType(SerializedED *SED, LPTSTR buf/*1024*/, int bufSize/*1024*/)
{
	DM("GetSubType(ppi", "SED", SED, "buf", buf, "bufSize", bufSize);
	std::string id = (*ED(SED).json)["ID"];
	id = id.substr(0, bufSize-1) + '\0';
	std::copy(id.begin(), id.end(), buf);
}

DWORD MMF2Func GetInfos(int Which)
{
	DM("GetInfos(i", "Which", Which);
	switch(Which)
	{
	case KGI_VERSION:	return EXT_VERSION3;
	case KGI_PLUGIN:	return EXT_PLUGIN_VERSION2;
	case KGI_PRODUCT:
//						return PRODUCT_VERSION_HOME;		//TGF2 Full
						return PRODUCT_VERSION_STANDARD;	//MMF2 Standard
//						return PRODUCT_VERSION_DEV;			//MMF2 Developer
	case KGI_BUILD:		return 257;
	case KGI_UNICODE:	return
		#ifdef UNICODE
			TRUE
		#else
			FALSE
		#endif
		;
	case KGI_MULTIPLESUBTYPE: return TRUE;
	}
	return 0;
}
short MMF2Func Action(RD *rd, long param1, long param2);
long MMF2Func Condition(RD *rd, long param1, long param2);
long MMF2Func Expression(RD *rd, long param1);
short MMF2Func GetRunObjectInfos(mv *mV, kpxRunInfos *Info)
{	DST();
	DM("GetRunObjectInfos(pp", "mV", mV, "Info", Info);

	Info->identifier = *reinterpret_cast<long const *>("Wig+");
	Info->version = 0;

	Info->numOfConditions = 1;
	Info->numOfActions = 1;
	Info->numOfExpressions = 1;

	Info->actions = &Action;
	Info->conditions = &Condition;
	Info->expressions = &Expression;

	Info->editDataSize = sizeof(SerializedED);

	Info->windowProcPriority = 100;

	Info->editFlags = OEFLAG_VALUES|OEFLAG_ANIMATIONS|OEFLAG_MOVEMENTS|OEFLAG_SPRITES|OEFLAG_RUNBEFOREFADEIN;
	Info->editPrefs = 0;

	return TRUE;
}
void MMF2Func GetObjInfos(mv *mV, void *, LPTSTR ObjName/*255*/, LPTSTR ObjAuthor/*255*/, LPTSTR ObjCopyright/*255*/, LPTSTR ObjComment/*1024*/, LPTSTR ObjHttp/*255*/)
{	DST();
	DM("GetObjInfos(pppppp", "mV", mV, "ObjName", ObjName, "ObjAuthor", ObjAuthor, "ObjCopyright", ObjCopyright, "ObjComment", ObjComment, "ObjHttp", ObjHttp);
	_tcscpy(ObjName,		_T("Widget+"));
	_tcscpy(ObjAuthor,		_T("Nicholas \"LB\" Braden"));
	_tcscpy(ObjCopyright,	_T("LB-Stuff.com"));
	_tcscpy(ObjComment,		_T("Given a Widget Definition File (*.wdf), ")
							_T("allows you to create your own extension ")
							_T("with events powering the Actions, ")
							_T("Conditions, and Expressions."));
	_tcscpy(ObjHttp,		_T("http://www.LB-Stuff.com/"));
}
LPCTSTR MMF2Func GetHelpFileName()
{
	DM("GetHelpFileName(", 0);
	return _T("Widget.chm");
}

LPCTSTR *MMF2Func GetDependencies()
{
	DM("GetDependencies(", 0);
	return 0;
}

int MMF2Func LoadObject(mv *mV, LPCSTR Filename, SerializedED *SED, int)
{	DST();
	DM("LoadObject(psp", "mV", mV, "Filename", Filename, "SED", SED);
	return 0;
}
void MMF2Func UnloadObject(mv *mV, SerializedED *SED, int)
{	DST();
	DM("UnloadObject(pp", "mV", mV, "SED", SED);
}

HGLOBAL MMF2Func UpdateEditStructure(mv *mV, SerializedED *OldSED)
{	DST();
	DM("UpdateEditStructure(pp", "mV", mV, "OldSED", OldSED);
	return 0;
}
void MMF2Func UpdateFileNames(mv *mV, LPTSTR AppName, SerializedED *SED, void (__stdcall *Update)(LPTSTR, LPTSTR))
{	DST();
	DM("UpdateFileNames(ptpp", "mV", mV, "AppName", (AppName? AppName : _T("<null>")), "SED", SED, "Update()", Update);
}

int MMF2Func EnumElts(mv *mV, SerializedED *SED, ENUMELTPROC enumProc, ENUMELTPROC undoProc, LPARAM lp1, LPARAM lp2)
{	DST();
	DM("EnumElts(ppppii", "mV", mV, "SED", SED, "enumProc()", enumProc, "undoProc()", undoProc, "lp1", lp1, "lp2", lp2);
	return 0;
}
