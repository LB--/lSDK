#include "lSDK/UnicodeUtilities.hpp"

#include <memory>
#include <stdexcept>

#include <Windows.h>

namespace lSDK
{
	auto wide_from_narrow(string_view8_t const &s)
	-> string16_t
	{
		if(s.empty())
		{
			return {};
		}
		auto const len = MultiByteToWideChar(CP_UTF8, 0, s.data(), s.size(), NULL, 0);
		if(len <= 0)
		{
#ifdef DEBUG
			throw std::runtime_error{"Cannot widen utf8 string: "+string8_t{s}};
#else
			return {std::cbegin(s), std::cend(s)};
#endif
		}
		auto buf = std::make_unique<string16_t::value_type[]>(static_cast<std::size_t>(len));
		auto const result = MultiByteToWideChar(CP_UTF8, 0, s.data(), s.size(), buf.get(), len);
		if(result <= 0)
		{
#ifdef DEBUG
			throw std::runtime_error{"Cannot widen utf8 string: "+string8_t{s}};
#else
			return {std::cbegin(s), std::cend(s)};
#endif
		}
		return string16_t{buf.get(), static_cast<std::size_t>(len)};
	}
	auto narrow_from_wide(string_view16_t const &s)
	-> string8_t
	{
		if(s.empty())
		{
			return {};
		}
		auto const len = WideCharToMultiByte(CP_UTF8, 0, s.data(), s.size(), NULL, 0, NULL, NULL);
		if(len <= 0)
		{
#ifdef DEBUG
			throw std::runtime_error{"Cannot narrow wide string"};
#else
			string8_t ret;
			ret.reserve(s.size());
			for(auto const &c : s)
			{
				ret += static_cast<string8_t::value_type>(c);
			}
			return ret;
#endif
		}
		auto buf = std::make_unique<string8_t::value_type[]>(static_cast<std::size_t>(len));
		auto const result = WideCharToMultiByte(CP_UTF8, 0, s.data(), s.size(), buf.get(), len, NULL, NULL);
		if(result <= 0)
		{
#ifdef DEBUG
			throw std::runtime_error{"Cannot narrow wide string"};
#else
			string8_t ret;
			ret.reserve(s.size());
			for(auto const &c : s)
			{
				ret += static_cast<string8_t::value_type>(c);
			}
			return ret;
#endif
		}
		return string8_t{buf.get(), static_cast<std::size_t>(len)};
	}
}
