#include "EditData.hpp"
#include "FusionAPI.hpp"

#ifdef FUSION_GET_COMPATIBILITY
auto FUSION_API GetInfos(std::int32_t const which) noexcept
-> std::uint32_t
{
	switch(which)
	{
	case KGI_VERSION:
		return FUSION_GET_COMPATIBILITY_VERSION;
	case KGI_PLUGIN:
		return FUSION_GET_COMPATIBILITY_PLUGIN;
	case KGI_PRODUCT:
//		return PRODUCT_VERSION_HOME;     //TGF2 Full
		return PRODUCT_VERSION_STANDARD; //MMF2 Standard
//		return PRODUCT_VERSION_DEV;      //MMF2 Developer
	case KGI_BUILD:
		return 290;
	case KGI_UNICODE:
		return FUSION_GET_COMPATIBILITY_UNICODE;
	case KGI_MULTIPLESUBTYPE:
		return FUSION_GET_COMPATIBILITY_MULTIPLE_SUBTYPES;
	}
	return 0;
}
#endif

#ifdef FUSION_ACTIONS
fusion::action_func action_sleep_for, action_sleep_one_second, action_show_dialog;
#endif
#ifdef FUSION_CONDITIONS
fusion::condition_func condition_compare_numbers, condition_compare_strings, condition_on_dialog_closed, condition_on_dialog_button;
#endif
#ifdef FUSION_EXPRESSIONS
fusion::expression_func expression_add_numbers, expression_add_strings, expression_pressed_button;
#endif

#ifdef FUSION_GET_EXTENSION_INFO
auto FUSION_API GetRunObjectInfos(mv *const mV, kpxRunInfos *const run_info) noexcept
-> std::int16_t
{
	if(!run_info)
	{
		return FUSION_GET_EXTENSION_INFO_FAILURE;
	}

	run_info->identifier = *reinterpret_cast<long const *>("lSDK");
	run_info->version = SerializedEditData::CURRENT_VERSION;

	run_info->editDataSize = sizeof(SerializedEditData);

	run_info->windowProcPriority = 100;

	run_info->editFlags = FUSION_OEFLAGS;
	run_info->editPrefs = 0;

	static fusion::    action_func_pointer     actions[] = {action_sleep_for, action_sleep_one_second, action_show_dialog};
	static fusion:: condition_func_pointer  conditions[] = {condition_compare_numbers, condition_compare_strings, condition_on_dialog_closed, condition_on_dialog_button};
	static fusion::expression_func_pointer expressions[] = {expression_add_numbers, expression_add_strings, expression_pressed_button};

	run_info->    actions = static_cast<fusion::    action_func_array>(    actions);
	run_info-> conditions = static_cast<fusion:: condition_func_array>( conditions);
	run_info->expressions = static_cast<fusion::expression_func_array>(expressions);

	run_info->numOfActions = 3;
	run_info->numOfConditions = 4;
	run_info->numOfExpressions = 3;

	return FUSION_GET_EXTENSION_INFO_SUCCESS;
}
#endif
