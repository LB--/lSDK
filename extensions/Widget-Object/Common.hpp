#ifndef CommonDeclarations_HeaderPlusPlus
#define CommonDeclarations_HeaderPlusPlus
#include "lSDK.hpp"

extern HINSTANCE DLL;

#include "lSDK/UnicodeUtilities.hpp"

#ifdef DEBUG
void DebugLog(char const *func, ...);
#define DM(Func, ...) DebugLog(Func, __VA_ARGS__)
#else
#define DM(NotInDebugMode, ...)
#endif

#define ExtensionVersionNumber 0

#include "json.h"

#include "EditData.hpp"
#include "RunData.hpp"

#endif
