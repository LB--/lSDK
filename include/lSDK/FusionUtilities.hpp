#ifndef lSDK_FusionUtilities_HeaderPlusPlus
#define lSDK_FusionUtilities_HeaderPlusPlus

#include <any>
#include <functional>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "FusionAPI.hpp"
#include "lSDK.hpp"

namespace lSDK
{
	#if defined(FUSION_GET_ACTION_INFO_ARRAY) || defined(FUSION_GET_CONDITION_INFO_ARRAY) || defined(FUSION_GET_EXPRESSION_INFO_ARRAY)
	template<std::int16_t Id, std::int16_t Flags, std::int16_t... ParamTypes>
	constexpr auto constant_ace_info() noexcept
	-> fusion::ace_info_array
	{
		static constexpr std::int16_t info[3+2*sizeof...(ParamTypes)] = {Id, Flags, sizeof...(ParamTypes), ParamTypes..., (0*ParamTypes)...};
		return info;
	}
	#endif

	inline auto call_runtime_function(headerObject &header_object, std::size_t const function_id, std::uint32_t const wparam = 0, std::int32_t const lparam = 0)
	#ifndef DEBUG
	noexcept
	#endif
	-> std::int32_t
	{
		#ifdef DEBUG
		if(function_id >= KPX_MAXFUNCTIONS)
		{
			throw std::out_of_range{"Invalid runtime function: "+std::to_string(function_id)};
		}
		if(!header_object.hoAdRunHeader)
		{
			throw std::runtime_error{"hoAdRunHeader is null"};
		}
		#endif
		auto const func = header_object.hoAdRunHeader->rh4.rh4KpxFunctions[function_id].routine;
		#ifdef DEBUG
		if(!func)
		{
			throw std::runtime_error{"Runtime function is null: "+std::to_string(function_id)};
		}
		#endif
		return func(&header_object, wparam, lparam);
	}

	#ifdef LSDK_PARAMS_HELPER
	namespace
	{
		template<std::size_t NumParams>
		struct ActionOrConditionParamsState
		{
			ActionOrConditionParamsState(headerObject &header_object, std::int32_t const param0, std::int32_t const param1) noexcept
			: header_object(header_object)
			, param0{param0}
			, param1{param1}
			{
			}

			auto next_generic()
			#ifndef DEBUG
			noexcept
			#endif
			-> std::int32_t
			{
				#ifdef DEBUG
				if(++current_param > NumParams)
				{
					throw std::runtime_error{"Trying to take too many parameters"};
				}
				#endif
				if constexpr(NumParams <= 2)
				{
					if(first_param)
					{
						first_param = false;
						return param0;
					}
					return param1;
				}
				else if constexpr(true)
				{
					return call_runtime_function(header_object, RFUNCTION_GETPARAM, 0xFFFFFFFF); //CNC_GetParameter
				}
			}

		protected:
			headerObject &header_object;
			std::int32_t const param0, param1;
			bool first_param = true;
			#ifdef DEBUG
			std::size_t current_param = 0;
			#endif
		};
		template<std::size_t NumParams>
		struct ExpressionParamsState
		{
			ExpressionParamsState(headerObject &header_object, std::int32_t const params_handle) noexcept
			: header_object(header_object)
			, params_handle{params_handle}
			{
			}

		protected:
			headerObject &header_object;
			std::int32_t const params_handle;
			std::size_t func = RFUNCTION_GETPARAM1;
			#ifdef DEBUG
			std::size_t current_param = 0;
			#endif
		};
		template<FusionAceType Type, std::size_t NumParams>
		using ParamsState = std::conditional_t<Type == FusionAceType::Expression, ExpressionParamsState<NumParams>, ActionOrConditionParamsState<NumParams>>;
	}
	template<FusionAceType Type, std::size_t NumParams>
	struct FusionParams final
	: ParamsState<Type, NumParams>
	{
		using ParamsState<Type, NumParams>::ParamsState;

		#ifdef DEBUG
		~FusionParams() noexcept(false)
		{
			if(std::uncaught_exceptions() == 0 && (NumParams > 2 || Type == FusionAceType::Expression) && current_param < NumParams)
			{
				throw std::runtime_error{"Not all parameters were consumed, this will cause Fusion to crash"};
			}
		}

		void verify_next_parameter_type(std::int16_t const type) const
		{
			if(!header_object.hoCurrentParam)
			{
				throw std::runtime_error{"hoCurrentParam is null"};
			}
			if(header_object.hoCurrentParam->evpSize == 0)
			{
				throw std::runtime_error{"There is no next parameter"};
			}
			if(header_object.hoCurrentParam->evpCode != type)
			{
				throw std::runtime_error{"Parameter type mismatch: "+std::to_string(header_object.hoCurrentParam->evpCode)+" != "+std::to_string(type)};
			}
		}
		#else
		void verify_next_parameter_type(std::int16_t const type) const noexcept = delete;
		#endif

		auto next_string()
		#ifndef DEBUG
		noexcept
		#endif
		-> lSDK::string_view_t
		{
			if constexpr(Type == FusionAceType::Expression)
			{
				#ifdef DEBUG
				if(++current_param > NumParams)
				{
					throw std::runtime_error{"Trying to take too many parameters"};
				}
				if constexpr(NumParams > 2 || Type == FusionAceType::Expression)
				{
					verify_next_parameter_type(PARAM_EXPSTRING);
				}
				#endif
				std::int32_t const result = call_runtime_function(header_object, func, TYPE_STRING, params_handle);
				func = RFUNCTION_GETPARAM2;
				return reinterpret_cast<lSDK::char_t const *const>(result);
			}
			else if constexpr(true)
			{
				return reinterpret_cast<lSDK::char_t const *const>(next_generic()); //CNC_GetStringParameter == CNC_GetParameter
			}
		}
		auto next_float()
		#ifndef DEBUG
		noexcept
		#endif
		-> std::conditional_t<(NumParams > 2) || Type == FusionAceType::Expression, float, double>
		{
			#ifdef DEBUG
			if(++current_param > NumParams)
			{
				throw std::runtime_error{"Trying to take too many parameters"};
			}
			if constexpr(NumParams > 2 || Type == FusionAceType::Expression)
			{
				verify_next_parameter_type(PARAM_EXPRESSION);
			}
			#endif
			if constexpr(Type == FusionAceType::Expression)
			{
				auto const result = call_runtime_function(header_object, func, TYPE_FLOAT, params_handle);
				func = RFUNCTION_GETPARAM2;
				return *reinterpret_cast<float const *const>(&result);
			}
			else if constexpr(NumParams <= 2)
			{
				CValue const &v0 = header_object.hoAdRunHeader->rh4.rh4ExpValue1;
				CValue const &v1 = header_object.hoAdRunHeader->rh4.rh4ExpValue2;
				if(first_param)
				{
					first_param = false;
					if(v0.m_type == TYPE_FLOAT)
					{
						return v0.m_double;
					}
					return static_cast<double>(param0);
				}
				if(v1.m_type == TYPE_FLOAT)
				{
					return v1.m_double;
				}
				return static_cast<double>(param1);
			}
			else if constexpr(true)
			{
				std::int32_t const result = call_runtime_function(header_object, RFUNCTION_GETPARAM, 2); //CNC_GetFloatParameter
				return *reinterpret_cast<float const *const>(&result);
			}
		}
		auto next_integer()
		#ifndef DEBUG
		noexcept
		#endif
		-> std::conditional_t<(NumParams > 2) || Type == FusionAceType::Expression, std::int32_t, std::intmax_t>
		{
			#ifdef DEBUG
			if(++current_param > NumParams)
			{
				throw std::runtime_error{"Trying to take too many parameters"};
			}
			if constexpr(NumParams > 2 || Type == FusionAceType::Expression)
			{
				verify_next_parameter_type(PARAM_EXPRESSION);
			}
			#endif
			if constexpr(Type == FusionAceType::Expression)
			{
				auto const result = call_runtime_function(header_object, func, TYPE_INT, params_handle);
				func = RFUNCTION_GETPARAM2;
				return result;
			}
			else if constexpr(NumParams <= 2)
			{
				CValue const &v0 = header_object.hoAdRunHeader->rh4.rh4ExpValue1;
				CValue const &v1 = header_object.hoAdRunHeader->rh4.rh4ExpValue2;
				if(first_param)
				{
					first_param = false;
					if(v0.m_type == TYPE_FLOAT)
					{
						return static_cast<std::intmax_t>(v0.m_double);
					}
					return param0;
				}
				if(v1.m_type == TYPE_FLOAT)
				{
					return static_cast<std::intmax_t>(v1.m_double);
				}
				return param1;
			}
			else if constexpr(true)
			{
				return call_runtime_function(header_object, RFUNCTION_GETPARAM, 0); //CNC_GetIntParameter
			}
		}
	};
	#endif //LSDK_PARAMS_HELPER

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
