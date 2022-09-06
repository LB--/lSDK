#ifndef lSDK_UnicodeUtilities_HeaderPlusPlus
#define lSDK_UnicodeUtilities_HeaderPlusPlus

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>

namespace lSDK
{
	#define NSL(s) u8##s
	#define WSL(s) L##s
#ifdef UNICODE
	#define TSL(s) L##s
	template<typename NarrowType, typename WideType>
	using unicode_type = WideType;
#else
	#define TSL(s) u8##s
	template<typename NarrowType, typename WideType>
	using unicode_type = NarrowType;
#endif
	using string8_t  = std:: string;
	using string16_t = std::wstring;
	using string_t = unicode_type<string8_t, string16_t>;
	using char_t = string_t::value_type;
	using string_view8_t  = std:: string_view;
	using string_view16_t = std::wstring_view;
	using string_view_t = unicode_type<string_view8_t, string_view16_t>;

	string16_t wide_from_narrow(string_view8_t , std::optional<std::uint32_t> codepage = std::nullopt);
	string8_t  narrow_from_wide(string_view16_t, std::optional<std::uint32_t> codepage = std::nullopt);

	string16_t inline   wide_from(string_view16_t   const s, std::optional<std::uint32_t> const /******/ = std::nullopt){ return string16_t{s};                 }
	string16_t inline   wide_from(string_view8_t    const s, std::optional<std::uint32_t> const codepage = std::nullopt){ return wide_from_narrow(s, codepage); }
	string8_t  inline narrow_from(string_view8_t    const s, std::optional<std::uint32_t> const /******/ = std::nullopt){ return string8_t{s};                  }
	string8_t  inline narrow_from(string_view16_t   const s, std::optional<std::uint32_t> const codepage = std::nullopt){ return narrow_from_wide(s, codepage); }
#ifdef UNICODE
	string16_t inline string_t_from(string_view8_t  const s, std::optional<std::uint32_t> const codepage = std::nullopt){ return wide_from_narrow(s, codepage); }
	string16_t inline string_t_from(string_view16_t const s, std::optional<std::uint32_t> const /******/ = std::nullopt){ return string16_t{s};                 }
#else
	string8_t  inline string_t_from(string_view8_t  const s, std::optional<std::uint32_t> const /******/ = std::nullopt){ return string8_t{s};                  }
	string8_t  inline string_t_from(string_view16_t const s, std::optional<std::uint32_t> const codepage = std::nullopt){ return narrow_from_wide(s, codepage); }
#endif

	template<typename Numeric>
	auto string_t_from_numeric(Numeric const numeric) noexcept(noexcept(std::to_string(numeric)))
	-> string_t
	{
#ifdef UNICODE
		return std::to_wstring(numeric);
#else
		return std::to_string(numeric);
#endif
	}

	template<typename CharacterTo, typename CharacterFrom>
	auto convert_to(std::basic_string_view<CharacterFrom> const s, [[maybe_unused]] std::optional<std::uint32_t> const codepage = std::nullopt)
	-> std::basic_string<CharacterTo>
	{
		static_assert(
			std::is_same_v<CharacterTo, CharacterFrom> ||
			std::is_same_v<CharacterTo, string8_t::value_type> ||
			std::is_same_v<CharacterTo, string16_t::value_type>
		);
		if constexpr(std::is_same_v<CharacterTo, CharacterFrom>)
		{
			return std::basic_string<CharacterTo>{s};
		}
		else if constexpr(std::is_same_v<CharacterTo, string8_t::value_type>)
		{
			return narrow_from(s, codepage);
		}
		else if constexpr(std::is_same_v<CharacterTo, string16_t::value_type>)
		{
			return wide_from(s, codepage);
		}
	}
	template<typename CharacterTo, typename CharacterFrom>
	auto convert_to(std::basic_string<CharacterFrom> const s, std::optional<std::uint32_t> const codepage = std::nullopt)
	-> std::basic_string<CharacterTo>
	{
		return convert_to<CharacterTo, CharacterFrom>(static_cast<std::basic_string_view<CharacterFrom>>(s), codepage);
	}
}

#endif
