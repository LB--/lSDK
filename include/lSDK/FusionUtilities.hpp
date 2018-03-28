#ifndef lSDK_FusionUtilities_HeaderPlusPlus
#define lSDK_FusionUtilities_HeaderPlusPlus

#include <any>
#include <functional>
#include <stdexcept>
#include <string>

#include "FusionAPI.hpp"

namespace lSDK
{
	inline auto call_runtime_function(headerObject &header_object, std::size_t const function_id, std::uint32_t const wparam = 0, std::int32_t const lparam = 0)
	-> std::int32_t
	{
		if(function_id >= KPX_MAXFUNCTIONS)
		{
			throw std::out_of_range{"Invalid runtime function: "+std::to_string(function_id)};
		}
		if(!header_object.hoAdRunHeader)
		{
			throw std::runtime_error{"hoAdRunHeader is null"};
		}
		auto const func = header_object.hoAdRunHeader->rh4.rh4KpxFunctions[function_id].routine;
		if(!func)
		{
			throw std::runtime_error{"Runtime function is null: "+std::to_string(function_id)};
		}
		return func(&header_object, wparam, lparam);
	}

	template<typename T>
	void trigger_condition(headerObject &header_object, std::int16_t const condition_id, T &param)
	{
		std::any wrapper {std::make_any<T &>(std::ref(param))};
		static_assert(sizeof(std::any *) == sizeof(std::int32_t));
		std::int32_t const p = reinterpret_cast<std::int32_t>(&wrapper);
		call_runtime_function(header_object, RFUNCTION_GENERATEEVENT, condition_id, p);
	}
	inline bool has_triggered_condition_param(headerObject &header_object)
	{
		return header_object.hoAdRunHeader && header_object.hoAdRunHeader->rhCurParam[0];
	}
	template<typename T>
	auto get_triggered_condition_param(headerObject &header_object)
	-> T &
	{
		if(header_object.hoAdRunHeader)
		{
			if(std::int32_t const p = header_object.hoAdRunHeader->rhCurParam[0])
			{
				std::any &wrapper = *reinterpret_cast<std::any *>(p);
				return std::any_cast<T &>(wrapper);
			}
			throw std::runtime_error{"Parameter for triggered condition is null"};
		}
		throw std::runtime_error{"hoAdRunHeader is null"};
	}
}

#endif
