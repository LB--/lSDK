#ifndef lSDK_HeaderPlusPlus
#define lSDK_HeaderPlusPlus

#include "lSDK/UnicodeUtilities.hpp"

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>

namespace lSDK
{
	template<typename CharFrom, typename CharTo>
	bool fill_buffer(CharTo *const buffer, std::intmax_t const max_len, std::basic_string_view<CharFrom> const &str)
	{
		if(!buffer)
		{
			throw std::runtime_error{"Pointer to buffer is null!"};
		}
		if(max_len > 0)
		{
			buffer[0] = TSL('\0');
		}
		if(max_len < 0)
		{
			throw std::runtime_error{"Negative size for buffer: "+std::to_string(max_len)};
		}
		if(max_len == 0)
		{
			return str.empty();
		}
		std::size_t const max_size = static_cast<std::size_t>(max_len-1);
		auto const tstr = convert_to<CharTo>(str);
		auto const begin = std::cbegin(tstr);
		auto const end = begin + std::min(tstr.length(), max_size);
		*std::copy(begin, end, buffer) = 0;
#ifdef DEBUG
		if(tstr.length() > max_size)
		{
			throw std::runtime_error{"String is too large to fit in size "+std::to_string(max_len)+" buffer:\n"+narrow_from(str)};
		}
#endif
		return tstr.length() <= max_size;
	}
	template<typename CharFrom, typename CharTo>
	bool fill_buffer(CharTo *const buffer, std::intmax_t const max_len, CharFrom const *const str)
	{
		return fill_buffer<CharFrom, CharTo>(buffer, max_len, static_cast<std::basic_string_view<CharFrom>>(str));
	}
	template<typename CharFrom, typename CharTo>
	bool fill_buffer(CharTo *const buffer, std::intmax_t const max_len, std::basic_string<CharFrom> const &str)
	{
		return fill_buffer<CharFrom, CharTo>(buffer, max_len, static_cast<std::basic_string_view<CharFrom>>(str));
	}

	enum struct FusionAceType
	{
		Action,
		Condition,
		Expression
	};
}

#endif
