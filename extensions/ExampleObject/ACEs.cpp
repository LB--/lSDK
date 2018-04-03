#include "FusionAPI.hpp"
#include "lSDK/FusionUtilities.hpp"
#include "RunData.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <thread>

#include <Windows.h>
#include <CommCtrl.h>

struct ConditionParamOnDialogClosed final
{
	int button_num = 0;
};

#ifdef FUSION_ACTIONS
auto FUSION_API action_sleep_for(RunData *const run_data, std::int32_t const param0, std::int32_t const param1) noexcept
-> std::int16_t
{
	CValue const &v0 = run_data->rHo.hoAdRunHeader->rh4.rh4ExpValue1; //only available for actions or conditions with less than 3 parameters
	if(v0.m_type == TYPE_FLOAT)
	{
		std::this_thread::sleep_for(std::chrono::duration<double>(v0.m_double));
	}
	else
	{
		std::this_thread::sleep_for(std::chrono::seconds(param0));
	}
	return 0;
}

auto FUSION_API action_sleep_one_second(RunData *const run_data, std::int32_t const param0, std::int32_t const param1) noexcept
-> std::int16_t
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	return 0;
}

auto FUSION_API action_show_dialog(RunData *const run_data, std::int32_t const param0, std::int32_t const param1) noexcept
-> std::int16_t
{
	lSDK::FusionParams<lSDK::FusionAceType::Action, 10> params (run_data->rHo, param0, param1);
	auto const title = params.next_string();
	auto const instruction = params.next_string();
	auto const content = params.next_string();
	auto const icon_num = params.next_integer();
	auto const button_ok = params.next_integer();
	auto const button_yes = params.next_integer();
	auto const button_no = params.next_integer();
	auto const button_cancel = params.next_integer();
	auto const button_retry = params.next_integer();
	auto const button_close = params.next_integer();

	auto icon = TD_ERROR_ICON;
	if(icon_num == 1)
	{
		icon = TD_INFORMATION_ICON;
	}
	else if(icon_num == 2)
	{
		icon = TD_SHIELD_ICON;
	}
	else if(icon_num == 3)
	{
		icon = TD_WARNING_ICON;
	}

	TASKDIALOG_COMMON_BUTTON_FLAGS button_flags = 0;
	if(button_ok)
	{
		button_flags |= TDCBF_OK_BUTTON;
	}
	if(button_yes)
	{
		button_flags |= TDCBF_YES_BUTTON;
	}
	if(button_no)
	{
		button_flags |= TDCBF_NO_BUTTON;
	}
	if(button_cancel)
	{
		button_flags |= TDCBF_CANCEL_BUTTON;
	}
	if(button_retry)
	{
		button_flags |= TDCBF_RETRY_BUTTON;
	}
	if(button_close)
	{
		button_flags |= TDCBF_CLOSE_BUTTON;
	}

	int pressed = 0;
	auto const result = TaskDialog(run_data->rHo.hoAdRunHeader->rhHMainWin, fusion::DLL, title.data(), instruction.data(), content.data(), button_flags, icon, &pressed);
	if(pressed != 0 && result == S_OK)
	{
		ConditionParamOnDialogClosed param;
		switch(pressed)
		{
		case IDCANCEL:
			param.button_num = 1;
			break;
		case IDNO:
			param.button_num = 2;
			break;
		case IDOK:
			param.button_num = 3;
			break;
		case IDRETRY:
			param.button_num = 4;
			break;
		case IDYES:
			param.button_num = 5;
			break;
		}
		lSDK::trigger_condition(run_data->rHo, 2, param);
		lSDK::trigger_condition(run_data->rHo, 3, param);
	}

	return 0;
}
#endif

#ifdef FUSION_CONDITIONS
auto FUSION_API condition_compare_numbers(RunData *const run_data, std::int32_t const param0, std::int32_t const param1) noexcept
-> std::int32_t
{
	//These are only available for actions or conditions with less than 3 parameters
	CValue const &v0 = run_data->rHo.hoAdRunHeader->rh4.rh4ExpValue1;
	CValue const &v1 = run_data->rHo.hoAdRunHeader->rh4.rh4ExpValue2;
	if(v0.m_type == TYPE_FLOAT)
	{
		double difference = 1.0;
		if(v1.m_type == TYPE_FLOAT)
		{
			difference = std::abs(v1.m_double - v0.m_double);
		}
		else
		{
			difference = std::abs(param1 - v0.m_double);
		}
		return (difference < 0.000001)? FUSION_CONDITIONS_TRUE : FUSION_CONDITIONS_FALSE;
	}
	else if(v1.m_type == TYPE_FLOAT)
	{
		return (std::abs(v1.m_double - param0) < 0.000001)? FUSION_CONDITIONS_TRUE : FUSION_CONDITIONS_FALSE;
	}
	return (param0 == param1)? FUSION_CONDITIONS_TRUE : FUSION_CONDITIONS_FALSE;
}

auto FUSION_API condition_compare_strings(RunData *const run_data, std::int32_t const param0, std::int32_t const param1) noexcept
-> std::int32_t
{
	lSDK::string_view_t string0 = reinterpret_cast<fusion::string_view>(param0);
	lSDK::string_view_t string1 = reinterpret_cast<fusion::string_view>(param1);
	return (string0 == string1)? FUSION_CONDITIONS_TRUE : FUSION_CONDITIONS_FALSE;
}

auto FUSION_API condition_on_dialog_closed(RunData *const run_data, std::int32_t const param0, std::int32_t const param1) noexcept
-> std::int32_t
{
	return FUSION_CONDITIONS_TRUE;
}
auto FUSION_API condition_on_dialog_button(RunData *const run_data, std::int32_t const param0, std::int32_t const param1) noexcept
-> std::int32_t
{
	auto &param = lSDK::get_triggered_condition_param<ConditionParamOnDialogClosed>(run_data->rHo);
	return (param0 == param.button_num)? FUSION_CONDITIONS_TRUE : FUSION_CONDITIONS_FALSE;
}
#endif

#ifdef FUSION_EXPRESSIONS
auto FUSION_API expression_add_numbers(RunData *const run_data, std::int32_t const params_handle) noexcept
-> std::int32_t
{
	lSDK::FusionParams<lSDK::FusionAceType::Expression, 3> params (run_data->rHo, params_handle);
	auto const type = params.next_integer();
	if(type == 1)
	{
		auto const number1 = params.next_float();
		auto const number2 = params.next_float();
		float const result = number1 + number2;
		run_data->rHo.hoFlags |= HOF_FLOAT;
		return *reinterpret_cast<std::int32_t const *const>(&result);
	}
	else
	{
		auto const number1 = params.next_integer();
		auto const number2 = params.next_integer();
		return number1 + number2;
	}
}

auto FUSION_API expression_add_strings(RunData *const run_data, std::int32_t const params_handle) noexcept
-> std::int32_t
{
	lSDK::FusionParams<lSDK::FusionAceType::Expression, 2> params (run_data->rHo, params_handle);
	auto const string0 = params.next_string();
	auto const string1 = params.next_string();
	std::int32_t const result = lSDK::call_runtime_function(run_data->rHo, RFUNCTION_GETSTRINGSPACE_EX, 0, (string0.length()+string1.length()+1)*sizeof(lSDK::char_t));
	auto const ptr = std::copy(std::cbegin(string0), std::cend(string0), reinterpret_cast<lSDK::char_t *>(result));
	*std::copy(std::cbegin(string1), std::cend(string1), ptr) = TSL('\0');
	run_data->rHo.hoFlags |= HOF_STRING;
	return result;
}

auto FUSION_API expression_pressed_button(RunData *const run_data, std::int32_t const params_handle) noexcept
-> std::int32_t
{
	if(lSDK::has_triggered_condition_param(run_data->rHo))
	{
		return lSDK::get_triggered_condition_param<ConditionParamOnDialogClosed>(run_data->rHo).button_num;
	}
	return 0;
}
#endif
