#ifndef lSDK_UnicodeUtilities_HeaderPlusPlus
#define lSDK_UnicodeUtilities_HeaderPlusPlus

#include <string>

namespace lSDK
{
	std::basic_string<wchar_t>  WidenStr(std::basic_string< char  > const &s);
	std::basic_string< char  > NarrowStr(std::basic_string<wchar_t> const &s);

	std::basic_string<wchar_t> inline EnsureWide  (std::basic_string<wchar_t> const &s){ return s; }
	std::basic_string<wchar_t> inline EnsureWide  (std::basic_string< char  > const &s){ return WidenStr(s); }
	std::basic_string< char  > inline EnsureNarrow(std::basic_string< char  > const &s){ return s; }
	std::basic_string< char  > inline EnsureNarrow(std::basic_string<wchar_t> const &s){ return NarrowStr(s); }
#ifdef UNICODE
	std::basic_string<wchar_T> inline EnsureTStr  (std::basic_string< char  > const &s){ return WidenStr(s); }
	std::basic_string<wchar_t> inline EnsureTStr  (std::basic_string<wchar_t> const &s){ return s; }
#else
	std::basic_string< char  > inline EnsureTStr  (std::basic_string< char  > const &s){ return s; }
	std::basic_string< char  > inline EnsureTStr  (std::basic_string<wchar_t> const &s){ return NarrowStr(s); }
#endif
}

#endif
