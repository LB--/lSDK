#include "lSDK/UnicodeUtilities.hpp"

#include <Windows.h>

namespace lSDK
{
	std::basic_string<wchar_t> WidenStr(std::basic_string<char> const &astr)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, astr.c_str(), -1, NULL, 0);
		wchar_t *wstr = new wchar_t[len];
		MultiByteToWideChar(CP_UTF8, 0, astr.c_str(), -1, wstr, len);
		std::basic_string<wchar_t> ustr (wstr);
		delete[] wstr;
		return ustr;
	}
	std::basic_string<char> NarrowStr(std::basic_string<wchar_t> const &ustr)
	{
		int len = WideCharToMultiByte(CP_UTF8, 0, ustr.c_str(), -1, NULL, 0, NULL, NULL);
		char *mstr = new char[len];
		WideCharToMultiByte(CP_UTF8, 0, ustr.c_str(), -1, mstr, len, NULL, NULL);
		std::basic_string<char> astr (mstr);
		delete[] mstr;
		return astr;
	}
}