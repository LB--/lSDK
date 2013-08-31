#include "Common.hpp"
#include <ctime>

HINSTANCE DLL (0);
BOOL WINAPI DllMain(HINSTANCE Dll, DWORD Reason, LPVOID)
{
	switch(Reason)
	{
	case DLL_PROCESS_ATTACH:
		{
			DLL = Dll;
			break;
		}
	}
	return TRUE;
}

#ifdef DEBUG
void DebugLog(const char *func, ...)
{
	static bool first = true;
	std::basic_ofstream<TCHAR> dbo ("C:/Widget_Debug.txt", std::ios_base::out|std::ios_base::ate|std::ios_base::app);
	if(first)
	{
		first = false;
		dbo << "Widget+ Object, Version #" << ExtensionVersionNumber << std::endl;
	}

	stdstring f (func);
	dbo << f.substr(0, f.find('(')) << std::endl;
	f = f.substr(f.find('(')+1);

	va_list Vars;
	va_start(Vars, func);
	for(stdstring::const_iterator it = f.begin(); it != f.end(); ++it)
	{
		dbo << '\t' << va_arg(Vars, const char *) << " = ";
		switch(*it)
		{
		case 'p':	dbo << "0x" << va_arg(Vars, void *);				break;
		case 'i':	dbo << va_arg(Vars, long);							break;
		case 's':	dbo << '"' << va_arg(Vars, const TCHAR *) << '"' ;	break;
		}
		dbo << std::endl;
	}
	va_end(Vars);
}
#endif

int MMF2Func InitExt(mv *mV, int Quiet)
{
	DM("InitExt(pi", "mV", mV, "Quiet", Quiet);
	srand(unsigned(time(0)));
	return 0;
}
int MMF2Func FreeExt(mv *mV)
{
	DM("FreeExt(p", "mV", mV);
	return 0;
}

DWORD MMF2Func GetInfos(int Which)
{
	DM("GetInfos(i", "Which", Which);
	switch(Which)
	{
	case KGI_VERSION:	return EXT_VERSION2;
	case KGI_PLUGIN:	return EXT_PLUGIN_VERSION1;
	case KGI_PRODUCT:
//						return PRODUCT_VERSION_HOME;		//TGF2 Full
						return PRODUCT_VERSION_STANDARD;	//MMF2 Standard
//						return PRODUCT_VERSION_DEV;			//MMF2 Developer
	case KGI_BUILD:		return 255;
	case KGI_UNICODE:	return
		#ifdef UNICODE
			TRUE
		#else
			FALSE
		#endif
		;
	}
	return 0;
}
short MMF2Func Action(RD *rd, long param1, long param2);
long MMF2Func Condition(RD *rd, long param1, long param2);
long MMF2Func Expression(RD *rd, long param1);
short MMF2Func GetRunObjectInfos(mv *mV, kpxRunInfos *Info)
{
	DM("GetRunObjectInfos(pp", "mV", mV, "Info", Info);

	Info->identifier = *reinterpret_cast<long*>("Wig+");
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
{
	DM("GetObjInfos(pppppp", "mV", mV, "ObjName", ObjName, "ObjAuthor", ObjAuthor, "ObjCopyright", ObjCopyright, "ObjComment", ObjComment, "ObjHttp", ObjHttp);
	_tcscpy(ObjName,		_T("Widget+"));
	_tcscpy(ObjAuthor,		_T("LB"));
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
{
	DM("LoadObject(psp", "mV", mV, "Filename", Filename, "SED", SED);
	return 0;
}
void MMF2Func UnloadObject(mv *mV, SerializedED *SED, int)
{
	DM("UnloadObject(pp", "mV", mV, "SED", SED);
}

HGLOBAL MMF2Func UpdateEditStructure(mv *mV, SerializedED *OldSED)
{
	DM("UpdateEditStructure(pp", "mV", mV, "OldSED", OldSED);
	return 0;
}
void MMF2Func UpdateFileNames(mv *mV, LPTSTR AppName, SerializedED *SED, void (__stdcall *Update)(LPTSTR, LPTSTR))
{
	DM("UpdateFileNames(pspp", "mV", mV, "AppName", AppName, "SED", SED, "Update()", Update);
}

int MMF2Func EnumElts(mv *mV, SerializedED *SED, ENUMELTPROC enumProc, ENUMELTPROC undoProc, LPARAM lp1, LPARAM lp2)
{
	DM("EnumElts(ppppii", "mV", mV, "SED", SED, "enumProc()", enumProc, "undoProc()", undoProc, "lp1", lp1, "lp2", lp2);
	return 0;
}
