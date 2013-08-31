#ifndef __StringConversion_HeaderPlusPlus__
#define __StringConversion_HeaderPlusPlus__
#include <sstream>
#include <string>
namespace s
{
	typedef std::basic_string<TCHAR> string;
	typedef std::basic_istringstream<TCHAR> istringstream;
	typedef std::basic_ostringstream<TCHAR> ostringstream;
}

template<typename To>
struct ConvTo
{
	static To f(const s::string &str)
	{
		s::istringstream ss (str);
		To temp;
		ss >> temp;
		return(temp);
	}
};
template<>
struct ConvTo<signed char>
{
	static signed char f(const s::string &str)
	{
		s::istringstream ss (str);
		signed short temp;
		ss >> temp;
		return(signed char(temp));
	}
};
template<>
struct ConvTo<unsigned char>
{
	static signed char f(const s::string &str)
	{
		s::istringstream ss (str);
		unsigned short temp;
		ss >> temp;
		return(unsigned char(temp));
	}
};
template<>
struct ConvTo<s::string>
{
	template<typename From>
	static s::string f(From num)
	{
		s::ostringstream ss;
		ss << num;
		return(ss.str());
	}
	template<>
	static s::string f<signed char>(signed char num)
	{
		s::ostringstream ss;
		ss << signed short(num);
		return(ss.str());
	}
	template<>
	static s::string f<unsigned char>(unsigned char num)
	{
		s::ostringstream ss;
		ss << unsigned short(num);
		return(ss.str());
	}
};

#endif
