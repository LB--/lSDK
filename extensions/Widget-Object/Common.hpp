#ifndef CommonDeclarations_HeaderPlusPlus
#define CommonDeclarations_HeaderPlusPlus
#include "lSDK.hpp"

extern HINSTANCE DLL;

#include "lSDK/UnicodeUtilities.hpp"

#ifdef DEBUG
void DebugLog(char const *func, ...);
#define DM(Func, ...) DebugLog(Func, __VA_ARGS__)
inline void DebugSubType(mv *mV)
{
	if(mV)
	{
		if(mV->subType)
		{
			DM("Sub Type(t", "", mV->subType);
		}
		else
		{
			DM("Sub Type(p", "", mV->subType);
		}
	}
	else
	{
		DM("");
		DM("mV is nullptr!");
		DM("");
	}
}
#define DST() DebugSubType(mV)
#else
#define DM(...)
#define DST()
#endif

#define ExtensionVersionNumber 0

#include "json.h"

#include "EditData.hpp"
#include "RunData.hpp"

#include <istream>

struct json_verifier
{
	json_value *json;
	std::string error;
	json_verifier(std::istream &def)
	{
		std::string str ((std::istreambuf_iterator<char>(def)), std::istreambuf_iterator<char>());
		json_settings options = {0};
		char err[json_error_max];
		json = json_parse_ex(&options, str.c_str(), str.length(), err);
		if(json)
		{
			if(json->type != json_object)
			{
				json_value_free(json), json = 0;
				error = "Invalid Widget Definition JSON";
				return;
			}
			bool  has_name = false
				, has_id = false
				, has_version = false
				, has_author = false
				, has_actions = false
				, has_conditions = false
				, has_expressions = false;
			std::string missing;
			for(std::size_t i = 0; i < json->u.object.length; ++i)
			{
				if(json->u.object.values[i].name == std::string("Name"))        has_name = true;
				if(json->u.object.values[i].name == std::string("ID"))          has_id = true;
				if(json->u.object.values[i].name == std::string("Version"))     has_version = true;
				if(json->u.object.values[i].name == std::string("Author"))      has_author = true;
				if(json->u.object.values[i].name == std::string("Actions"))     has_actions = true;
				if(json->u.object.values[i].name == std::string("Conditions"))  has_conditions = true;
				if(json->u.object.values[i].name == std::string("Expressions")) has_expressions = true;
			}
			if(!has_name)        missing += "Missing Name\r\n";
			if(!has_id)          missing += "Missing ID\r\n";
			if(!has_version)     missing += "Missing Version\r\n";
			if(!has_author)      missing += "Missing Author\r\n";
			if(!has_actions)     missing += "Missing Actions\r\n";
			if(!has_conditions)  missing += "Missing Conditions\r\n";
			if(!has_expressions) missing += "Missing Exressions\r\n";
			if(missing.size() > 0)
			{
				json_value_free(json), json = 0;
				error = missing;
			}
		}
		else error = err;
	}
	~json_verifier()
	{
		json_value_free(json), json = 0;
	}
};
template<typename Char>
std::basic_string<Char> EnsureWinNL(std::basic_string<Char> const &str)
{
	std::basic_string<Char> ret;
	if(str.size() > 0 && str[0] == Char('\n'))
	{
		ret += Char('\r');
	}
	for(std::basic_string<Char>::size_type i = 0; i < str.size(); ++i)
	{
		if(i > 0 && str[i] == Char('\n') && str[i-1] != Char('\r'))
		{
			ret += Char('\r');
		}
		ret += str[i];
	}
	return ret;
}

#endif
