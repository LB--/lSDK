#ifndef lSDK_UnicodeSupport_HeaderPlusPlus
#define lSDK_UnicodeSupport_HeaderPlusPlus

#include <string>

namespace lSDK
{
	std::basic_string<wchar_t>  WidenStr(std::basic_string< char  > const &s);
	std::basic_string< char  > NarrowStr(std::basic_string<wchar_t> const &s);

	std::basic_string<wchar_t> inline EnsureWide  (std::basic_string<wchar_t> const &s){ return s; }
	std::basic_string<wchar_t> inline EnsureWide  (std::basic_string< char  > const &s){ return WidenStr(s); }
	std::basic_string< char  > inline EnsureNarrow(std::basic_string< char  > const &s){ return s; }
	std::basic_string< char  > inline EnsureNarrow(std::basic_string<wchar_t> const &s){ return NarrowStr(s); }
}

#endif
