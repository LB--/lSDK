#ifndef CommonDeclarations_HeaderPlusPlus
#define CommonDeclarations_HeaderPlusPlus

#define _CRT_SECURE_NO_WARNINGS
#define	COXSDK
#define IN_EXT_VERSION2
#include "ccxhdr.h"
#define _WINDOWS
#include "Surface.h"
#undef _WINDOWS
#define MMF2Func __stdcall

extern HINSTANCE DLL;

#include "lSDK/UnicodeSupport.hpp"

#ifdef DEBUG
void DebugLog(char const *func, ...);
#define DM(Func, ...) DebugLog(Func, __VA_ARGS__)
#else
#define DM(NotInDebugMode, ...)
#endif

#define ExtensionVersionNumber 0

#include "EditData.hpp"
#include "RunData.hpp"

#endif
