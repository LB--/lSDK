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

#include <istream>

struct json_verifier
{
	json_value *json;
	char error[json_error_max];
	json_verifier(std::istream &def)
	{
		std::string str ((std::istreambuf_iterator<char>(def)), std::istreambuf_iterator<char>());
		json_settings options = {0};
		json = json_parse_ex(&options, str.c_str(), str.length(), error);
	}
	~json_verifier()
	{
		json_value_free(json), json = 0;
	}
};

#endif
