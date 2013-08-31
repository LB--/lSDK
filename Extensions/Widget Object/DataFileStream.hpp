#ifndef __DataFileStream_HeaderPlusPlus__
#define __DataFileStream_HeaderPlusPlus__

#include <fstream>
#include <string>

#include <tchar.h>

class OFS
{
	std::basic_ofstream<TCHAR> out;

	OFS(const OFS &);
	OFS &operator=(const OFS &);

	typedef std::basic_string<TCHAR> tstring;

public:
	const std::basic_ofstream<TCHAR> &File;
	OFS(const tstring &path) : out(path.c_str()), File(out)
	{
	}
	~OFS()
	{
	}

	template<typename T>
	OFS &operator<<(const T& t)
	{
		out.write(reinterpret_cast<const char *>(&t), sizeof(T));
		return *this;
	}
	template<>
	OFS &operator<< <TCHAR *>(TCHAR *const&cstr)
	{
		out.write(cstr, _tcslen(cstr));
		return *this;
	}
	template<>
	OFS &operator<< <const TCHAR *>(const TCHAR *const&cstr)
	{
		out.write(cstr, _tcslen(cstr));
		return *this;
	}
	template<>
	OFS &operator<<(const tstring &str)
	{
		out.write(str.c_str(), str.length());
		return *this;
	}
};

class IFS
{
	std::basic_ifstream<TCHAR> in;

	IFS(const IFS &);
	IFS &operator=(const IFS&);

	typedef std::basic_string<TCHAR> tstring;

public:
	std::basic_ifstream<TCHAR> &File;
	IFS(const tstring &path) : in(path.c_str()), File(in)
	{
	}
	~IFS()
	{
	}

	template<typename T>
	IFS &operator>>(T &t)
	{
		in.read(reinterpret_cast<char *>(&t), sizeof(T));
		return *this;
	}
	template<>
	IFS &operator>>(tstring &str)
	{
		str.clear();
		TCHAR ch;
		while(((*this) >> ch).File && ch)
		{
			str += ch;
		}
		return *this;
	}
};

#endif
