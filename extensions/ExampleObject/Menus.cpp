#include "FusionAPI.hpp"
#include "lSDK.hpp"
#include "lSDK/FusionMenu.hpp"
#include "lSDK/FusionUtilities.hpp"

#ifdef FUSION_GET_ACTION_MENU
auto FUSION_API GetActionMenu(mv *const mV, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept
-> HMENU
{
	using Menu = lSDK::ActionMenu;
	return Menu
	{{
		Menu::Separator{},
		Menu::Submenu{TSL("Sleep..."),
		{
			Menu::Item{0, TSL("...for a number of seconds")},
			Menu::Item{1, TSL("...for one second")}
		}},
		Menu::Item{2, TSL("Show dialog")},
		Menu::Separator{}
	}}.generate().release();
}
#endif
#ifdef FUSION_GET_CONDITION_MENU
auto FUSION_API GetConditionMenu(mv *const mV, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept
-> HMENU
{
	using Menu = lSDK::ConditionMenu;
	return Menu
	{{
		Menu::Separator{},
		Menu::Item{0, TSL("Compare two numbers")},
		Menu::Item{1, TSL("Compare two strings")},
		Menu::Separator{},
		Menu::Item{2, TSL("On Dialog Closed")},
		Menu::Item{3, TSL("On Dialog Button Pressed")},
		Menu::Separator{}
	}}.generate().release();
}
#endif
#ifdef FUSION_GET_EXPRESSION_MENU
auto FUSION_API GetExpressionMenu(mv *const mV, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept
-> HMENU
{
	using Menu = lSDK::ExpressionMenu;
	return Menu
	{{
		Menu::Separator{},
		Menu::Item{0, TSL("Add two numbers")},
		Menu::Item{1, TSL("Add two strings")},
		Menu::Separator{},
		Menu::Item{2, TSL("Get Pressed Dialog Button")},
		Menu::Separator{}
	}}.generate().release();
}
#endif

#ifdef FUSION_GET_ACTION_ID_FROM_ACTION_MENU_ID
auto FUSION_API GetActionCodeFromMenu(mv *const mV, std::int16_t const action_menu_id) noexcept
-> std::int16_t
{
	return lSDK::ActionMenu::ExtensionData::from_menu_id(action_menu_id);
}
#endif
#ifdef FUSION_GET_CONDITION_ID_FROM_CONDITION_MENU_ID
auto FUSION_API GetConditionCodeFromMenu(mv *const mV, std::int16_t const condition_menu_id) noexcept
-> std::int16_t
{
	return lSDK::ConditionMenu::ExtensionData::from_menu_id(condition_menu_id);
}
#endif
#ifdef FUSION_GET_EXPRESSION_ID_FROM_EXPRESSION_MENU_ID
auto FUSION_API GetExpressionCodeFromMenu(mv *const mV, std::int16_t const expression_menu_id) noexcept
-> std::int16_t
{
	return lSDK::ExpressionMenu::ExtensionData::from_menu_id(expression_menu_id);
}
#endif

#ifdef FUSION_GET_ACTION_INFO_ARRAY
auto FUSION_API GetActionInfos(mv *const mV, std::int16_t const action_id) noexcept
-> fusion::ace_info_array
{
	switch(action_id)
	{
	case 0:
		return lSDK::constant_ace_info<0, 0, PARAM_EXPRESSION>();
	case 1:
		return lSDK::constant_ace_info<1, 0>();
	case 2:
		return lSDK::constant_ace_info<2, 0, PARAM_EXPSTRING, PARAM_EXPSTRING, PARAM_EXPSTRING, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION>();
	}
	return nullptr;
}
#endif
#ifdef FUSION_GET_CONDITION_INFO_ARRAY
auto FUSION_API GetConditionInfos(mv *const mV, std::int16_t const condition_id) noexcept
-> fusion::ace_info_array
{
	switch(condition_id)
	{
	case 0:
		return lSDK::constant_ace_info<0, EVFLAGS_ALWAYS|EVFLAGS_NOTABLE, PARAM_EXPRESSION, PARAM_EXPRESSION>();
	case 1:
		return lSDK::constant_ace_info<1, EVFLAGS_ALWAYS|EVFLAGS_NOTABLE, PARAM_EXPSTRING, PARAM_EXPSTRING>();
	case 2:
		return lSDK::constant_ace_info<2, EVFLAGS_NOTABLE>();
	case 3:
		return lSDK::constant_ace_info<3, EVFLAGS_NOTABLE, PARAM_EXPRESSION>();
	}
	return nullptr;
}
#endif
#ifdef FUSION_GET_EXPRESSION_INFO_ARRAY
auto FUSION_API GetExpressionInfos(mv *const mV, std::int16_t const expression_id) noexcept
-> fusion::ace_info_array
{
	switch(expression_id)
	{
	case 0:
		return lSDK::constant_ace_info<0, 0, EXPPARAM_LONG, EXPPARAM_LONG, EXPPARAM_LONG>();
	case 1:
		return lSDK::constant_ace_info<1, EXPFLAG_STRING, EXPPARAM_STRING, EXPPARAM_STRING>();
	case 2:
		return lSDK::constant_ace_info<2, 0>();
	}
	return nullptr;
}
#endif

#ifdef FUSION_GET_ACTION_PARAM_NAME
void FUSION_API GetActionTitle(mv *const mV, std::int16_t const action_id, std::int16_t const param_id, fusion::string_buffer const param_name_buffer, std::int16_t const param_name_buffer_size) noexcept
{
	switch(action_id)
	{
	case 0:
		return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("Number of seconds (may be a floating point value)"));
	case 2:
		switch(param_id)
		{
		case 0:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("Dialog title"));
		case 1:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("Main instruction"));
		case 2:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("Content"));
		case 3:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("Icon (0 = error, 1 = info, 2 = shield, 3 = warning)"));
		case 4:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("1 = OK Button"));
		case 5:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("1 = Yes Button"));
		case 6:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("1 = No Button"));
		case 7:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("1 = Cancel Button"));
		case 8:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("1 = Retry Button"));
		case 9:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("1 = Close Button"));
		}
	}
}
#endif
#ifdef FUSION_GET_CONDITION_PARAM_NAME
void FUSION_API GetConditionTitle(mv *const mV, std::int16_t const condition_id, std::int16_t const param_id, fusion::string_buffer const param_name_buffer, std::int16_t const param_name_buffer_size) noexcept
{
	switch(condition_id)
	{
	case 0:
		switch(param_id)
		{
		case 0:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("Integer or Float A"));
		case 1:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("Integer or Float B"));
		}
	case 1:
		switch(param_id)
		{
		case 0:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("String A"));
		case 1:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("String B"));
		}
	case 3:
		return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("1 = cancel, 2 = no, 3 = ok, 4 = retry, 5 = yes"));
	}
}
#endif
#ifdef FUSION_GET_EXPRESSION_PARAM_NAME
void FUSION_API GetExpressionParam(mv *const mV, std::int16_t const expression_id, std::int16_t const param_id, fusion::string_buffer const param_name_buffer, std::int16_t const param_name_buffer_size) noexcept
{
	switch(expression_id)
	{
	case 0:
		switch(param_id)
		{
		case 0:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("0 = integers, 1 = floats"));
		case 1:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("Number A"));
		case 2:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("Number B"));
		}
	case 1:
		switch(param_id)
		{
		case 0:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("String A"));
		case 1:
			return (void)lSDK::fill_buffer(param_name_buffer, param_name_buffer_size, TSL("String B"));
		}
	}
}
#endif

#ifdef FUSION_GET_ACTION_DISPLAY_STRING
void FUSION_API GetActionString(mv *const mV, std::int16_t const action_id, fusion::string_buffer const display_string_buffer, std::int16_t const display_string_buffer_size) noexcept
{
	switch(action_id)
	{
	case 0:
		return (void)lSDK::fill_buffer(display_string_buffer, display_string_buffer_size, TSL("Sleep for %0 seconds"));
	case 1:
		return (void)lSDK::fill_buffer(display_string_buffer, display_string_buffer_size, TSL("Sleep for one second"));
	case 2:
		return (void)lSDK::fill_buffer(display_string_buffer, display_string_buffer_size, TSL("Show dialog, title = %0, instruction = %1, content = %2, OK = %3, Yes = %4, No = %5, Cancel = %6, Retry = %7, Close = %8, Icon = %9"));
	}
}
#endif
#ifdef FUSION_GET_CONDITION_DISPLAY_STRING
void FUSION_API GetConditionString(mv *const mV, std::int16_t const condition_id, fusion::string_buffer const display_string_buffer, std::int16_t const display_string_buffer_size) noexcept
{
	switch(condition_id)
	{
	case 0:
		return (void)lSDK::fill_buffer(display_string_buffer, display_string_buffer_size, TSL("%o: Are %0 and %1 equal?"));
	case 1:
		return (void)lSDK::fill_buffer(display_string_buffer, display_string_buffer_size, TSL("%o: Are %0 and %1 equal?"));
	case 2:
		return (void)lSDK::fill_buffer(display_string_buffer, display_string_buffer_size, TSL("%o: On dialog closed"));
	case 3:
		return (void)lSDK::fill_buffer(display_string_buffer, display_string_buffer_size, TSL("%o: On dialog button %0 pressed"));
	}
}
#endif

#ifdef FUSION_GET_EXPRESSION_EDITOR_STRING
void FUSION_API GetExpressionString(mv *const mV, std::int16_t const expression_id, fusion::string_buffer const editor_string_buffer, std::int16_t const editor_string_buffer_size) noexcept
{
	switch(expression_id)
	{
	case 0:
		return (void)lSDK::fill_buffer(editor_string_buffer, editor_string_buffer_size, TSL("add numbers("));
	case 1:
		return (void)lSDK::fill_buffer(editor_string_buffer, editor_string_buffer_size, TSL("add strings $("));
	case 2:
		return (void)lSDK::fill_buffer(editor_string_buffer, editor_string_buffer_size, TSL("pressed button("));
	}
}
#endif
