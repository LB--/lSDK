#ifndef __Common_HeaderPlusPlus__
#define __Common_HeaderPlusPlus__
#define _CRT_SECURE_NO_WARNINGS
#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#endif
#if defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <Windows.h>

#include <string>
typedef std::basic_string<TCHAR> stdstring;
#include <sstream>
typedef std::basic_stringstream<TCHAR> stdstringstream;
typedef std::basic_istringstream<TCHAR> stdistringstream;
typedef std::basic_ostringstream<TCHAR> stdostringstream;
std::basic_string<wchar_t> inline UfromA(std::basic_string<char> astr)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, astr.c_str(), -1, NULL, 0);
	wchar_t *wstr = new wchar_t[len];
	MultiByteToWideChar(CP_UTF8, 0, astr.c_str(), -1, wstr, len);
	std::basic_string<wchar_t> ustr (wstr);
	delete[] wstr;
	return ustr;
}
std::basic_string<char> inline AfromU(std::basic_string<wchar_t> ustr)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, ustr.c_str(), -1, NULL, 0, NULL, NULL);
	char *mstr = new char[len];
	WideCharToMultiByte(CP_UTF8, 0, ustr.c_str(), -1, mstr, len, NULL, NULL);
	std::basic_string<char> astr (mstr);
	delete[] mstr;
	return astr;
}

#include "StringConvert.hpp"
#include "DataFileStream.hpp"
#include <vector>
#include <map>

#ifdef DEBUG
void DebugLog(const char *func, ...);
#define DM(Func, ...) DebugLog(Func, __VA_ARGS__)
#else
#define DM(NotInDebugMode, ...)
#endif

#define	COXSDK
#define IN_EXT_VERSION2
#include "ccxhdr.h"
#define _WINDOWS
#include "Surface.h"
#undef _WINDOWS
#define MMF2Func __stdcall

#ifndef RUN_ONLY
	#define RunOnly_Start(alternate)
	#define RunOnly_End
#else
	#define RunOnly_Start(alternate) {alternate} /##*
	#define RunOnly_End *##/
#endif

extern HINSTANCE DLL;

#define ExtensionVersionNumber 0

#include "EditData.hpp"
#include "RunData.hpp"

#endif
