#ifndef FusionAPI_HeaderPlusPlus
#define FusionAPI_HeaderPlusPlus

#include <climits>
static_assert(CHAR_BIT == 8);

static_assert(sizeof(char    ) == 1);
static_assert(sizeof(wchar_t ) == 2);
static_assert(sizeof(short   ) == 2);
static_assert(sizeof(int     ) == 4);
static_assert(sizeof(unsigned) == 4);
static_assert(sizeof(long    ) == 4);
static_assert(sizeof(float   ) == 4);
static_assert(sizeof(double  ) == 8);

struct SerializedEditData;
struct RunData;
static_assert(sizeof(void *) == 4);
static_assert(sizeof(SerializedEditData *) == 4);
static_assert(sizeof(RunData *) == 4);

#include <Windows.h>
static_assert(sizeof(TCHAR ) == 1
||            sizeof(TCHAR ) == 2);
static_assert(sizeof(BOOL  ) == 4);
static_assert(sizeof(WPARAM) == 4);
static_assert(sizeof(LPARAM) == 4);
static_assert(sizeof(HMENU ) == 4);
static_assert(sizeof(HANDLE) == 4);

#define	COXSDK
#define IN_EXT_VERSION2
#define _WINDOWS
//#include "FusionAPI/Ccxhdr.h" //can't include because it defines IN_KPX
#include <stdio.h>
#include <tchar.h>
#define STDDLL_IMPORTS
#define IMGFLTMGR_IMPORTS
#define SNDMGR_IMPORTS
#define SURFACES_IMPORTS
#define ZCOMPDLL_IMPORTS
#define	RUN_TIME
#include "FusionAPI/PTYPE.H"
#include "FusionAPI/WinMacro.h"
#include "FusionAPI/colors.h"
#include "FusionAPI/Cnpdll.h"
#include "FusionAPI/cncr.h"
#include "FusionAPI/EVTCCX.H"
#include "FusionAPI/Props.h"
#include "FusionAPI/Ccx.h"

#include "FusionAPI/CfcFile.h"
#include "FusionAPI/ImageFlt.h"
#include "FusionAPI/ImgFlt.h"
#include "FusionAPI/Surface.h"
#include "FusionAPI/Cncf.h"
#include "FusionAPI/Mvt.h"
#undef _WINDOWS

static_assert(sizeof(mv *) == 4);
static_assert(sizeof(CPropValue *) == 4);

#define FUSION_API WINAPI

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace fusion
{
	extern HINSTANCE DLL;

	namespace
	{
		template<typename T, typename MemberT, std::size_t offset, typename = void>
		struct has_member final
		: std::false_type
		{
		};
		#define LSDK_HAS_MEMBER(MemberT, Name) \
		template<typename T, std::size_t offset> \
		struct has_member<T, MemberT, offset, decltype(T::Name, void())> final \
		{ \
			constexpr static bool value = std::is_same<MemberT, decltype(T::Name)>::value && offsetof(T, Name) == offset; \
		}
		LSDK_HAS_MEMBER(extHeader, eHeader);
		LSDK_HAS_MEMBER(headerObject, rHo);
		LSDK_HAS_MEMBER(rCom, rc);
		LSDK_HAS_MEMBER(rMvt, rm);
		LSDK_HAS_MEMBER(rAni, ra);
		LSDK_HAS_MEMBER(rSpr, rs);
		LSDK_HAS_MEMBER(rVal, rv);
		#undef LSDK_HAS_MEMBER
	}
	template<typename SerializedEditDataT = SerializedEditData>
	constexpr bool is_valid_editdata_structure() noexcept
	{
		static_assert(std::is_standard_layout_v<SerializedEditDataT>);
		static_assert(!std::is_default_constructible_v<SerializedEditDataT>);
		static_assert(!std::is_copy_constructible_v<SerializedEditDataT>);
		static_assert(!std::is_move_constructible_v<SerializedEditDataT>);
		static_assert(!std::is_copy_assignable_v<SerializedEditDataT>);
		static_assert(!std::is_move_assignable_v<SerializedEditDataT>);
		static_assert(!std::is_destructible_v<SerializedEditDataT>);

		static_assert(has_member<SerializedEditDataT, extHeader, 0>::value, "`extHeader eHeader;` must be the first data member of SerializedEditData");

		return true;
	}
	template<decltype(kpxRunInfos::editFlags) Flags, typename RunDataT = RunData>
	constexpr bool is_valid_rundata_structure() noexcept
	{
		static_assert(std::is_standard_layout_v<RunDataT>);
		static_assert(!std::is_default_constructible_v<RunDataT>);
		static_assert(!std::is_copy_constructible_v<RunDataT>);
		static_assert(!std::is_move_constructible_v<RunDataT>);
		static_assert(!std::is_copy_assignable_v<RunDataT>);
		static_assert(!std::is_move_assignable_v<RunDataT>);
		static_assert(!std::is_destructible_v<RunDataT>);

		static_assert(has_member<RunDataT, headerObject, 0>::value, "`headerObject rHo;` must be the first data member of RunData");
		if constexpr((Flags&OEFLAG_MOVEMENTS) != 0 || (Flags&OEFLAG_ANIMATIONS) != 0 || (Flags&OEFLAG_SPRITES) != 0)
		{
			static_assert(has_member<RunDataT, rCom, sizeof(headerObject)>::value, "`rCom rc;` must be immediately after `rHo`");
		}
		if constexpr((Flags&OEFLAG_MOVEMENTS) != 0)
		{
			static_assert(has_member<RunDataT, rMvt,
				sizeof(headerObject)+
				sizeof(rCom)
			>::value, "`rMvt rm;` must be immediately after `rc`");
		}
		if constexpr((Flags&OEFLAG_ANIMATIONS) != 0)
		{
			static_assert(has_member<RunDataT, rAni,
				sizeof(headerObject)+
				sizeof(rCom)+
				((Flags&OEFLAG_MOVEMENTS)? sizeof(rMvt) : 0)
			>::value, "`rAni ra;` must be after `rc` and/or `rm`");
		}
		if constexpr((Flags&OEFLAG_SPRITES) != 0)
		{
			static_assert(has_member<RunDataT, rSpr,
				sizeof(headerObject)+
				sizeof(rCom)+
				((Flags&OEFLAG_MOVEMENTS)? sizeof(rMvt) : 0)+
				((Flags&OEFLAG_ANIMATIONS)? sizeof(rAni) : 0)
			>::value, "`rSpr rs;` must be after `rc`, `rm`, and/or `ra`");
		}
		if constexpr((Flags&OEFLAG_VALUES) != 0)
		{
			static_assert(has_member<RunDataT, rVal,
				sizeof(headerObject)+
				(((Flags&OEFLAG_MOVEMENTS) || (Flags&OEFLAG_ANIMATIONS) || (Flags&OEFLAG_SPRITES))? sizeof(rCom) : 0)+
				((Flags&OEFLAG_MOVEMENTS)? sizeof(rMvt) : 0)+
				((Flags&OEFLAG_ANIMATIONS)? sizeof(rAni) : 0)+
				((Flags&OEFLAG_SPRITES)? sizeof(rSpr) : 0)
			>::value, "`rVal rv;` must be after `rc`, `rm`, `ra`, and/or `rs`");
		}

		return true;
	};

	using string_buffer = TCHAR *;
	static_assert(sizeof(string_buffer) == 4);

	using string_view = TCHAR const *;
	static_assert(sizeof(string_view) == 4);

	using wstring_view = WCHAR const *;
	static_assert(sizeof(wstring_view) == 4);

	using string_array_view = string_view const *;
	static_assert(sizeof(string_array_view) == 4);

	using debug_item_array = std::uint16_t const *;
	static_assert(sizeof(debug_item_array) == 4);

	using boolean = std::int32_t;
	static_assert(sizeof(boolean) == sizeof(BOOL));

	static_assert(sizeof(infosEventsV2::code   ) == 2);
	static_assert(sizeof(infosEventsV2::flags  ) == 2);
	static_assert(sizeof(infosEventsV2::nParams) == 2);
	using ace_info_array = std::int16_t const *;
	static_assert(sizeof(ace_info_array) == sizeof(LPINFOEVENTSV2));

	using     action_func = std::int16_t FUSION_API (RunData *const run_data, std::int32_t const param0, std::int32_t const param1) noexcept;
	using  condition_func = std::int32_t FUSION_API (RunData *const run_data, std::int32_t const param0, std::int32_t const param1) noexcept;
	using expression_func = std::int32_t FUSION_API (RunData *const run_data, std::int32_t const params_handle) noexcept;

	using     action_func_pointer =     action_func *;
	using  condition_func_pointer =  condition_func *;
	using expression_func_pointer = expression_func *;

	static_assert(sizeof(    action_func_pointer) == 4);
	static_assert(sizeof( condition_func_pointer) == 4);
	static_assert(sizeof(expression_func_pointer) == 4);

	using     action_func_array =     action_func_pointer *;
	using  condition_func_array =  condition_func_pointer *;
	using expression_func_array = expression_func_pointer *;

	static_assert(sizeof(kpxRunInfos::    actions) == sizeof(    action_func_array));
	static_assert(sizeof(kpxRunInfos:: conditions) == sizeof( condition_func_array));
	static_assert(sizeof(kpxRunInfos::expressions) == sizeof(expression_func_array));
}

#define FUSION_MENU_ACTIONS_FIRST     25000
#define FUSION_MENU_ACTIONS_LAST      25999
#define FUSION_MENU_CONDITIONS_FIRST  26000
#define FUSION_MENU_CONDITIONS_LAST   26999
#define FUSION_MENU_EXPRESSIONS_FIRST 27000
#define FUSION_MENU_EXPRESSIONS_LAST  27999

// General

#define FUSION_DLL_MAIN
BOOL WINAPI DllMain(HINSTANCE dll, DWORD reason, LPVOID reserved) noexcept;

#define FUSION_INITIALIZE
#define FUSION_INITIALIZE_FAILURE -1
#define FUSION_INITIALIZE_SUCCESS 0
std::int32_t FUSION_API InitExt(mv *const mV, fusion::boolean const quiet) noexcept;

#define FUSION_FREE
#define FUSION_FREE_SUCCESS 0
std::int32_t FUSION_API FreeExt(mv *const mV) noexcept;

#define FUSION_GET_COMPATIBILITY
#define FUSION_GET_COMPATIBILITY_VERSION EXT_VERSION3
#define FUSION_GET_COMPATIBILITY_PLUGIN EXT_PLUGIN_VERSION2
#define FUSION_GET_COMPATIBILITY_UNICODE ((sizeof(TCHAR) != 1)? TRUE : FALSE)
std::uint32_t FUSION_API GetInfos(std::int32_t const which) noexcept;

#ifdef FUSION_MULTIPLE_SUBTYPES

#define FUSION_GET_SUBTYPE
#define FUSION_GET_COMPATIBILITY_MULTIPLE_SUBTYPES TRUE
void FUSION_API GetSubType(SerializedEditData const *const serialized_edit_data, fusion::string_buffer const subtype_buffer, std::int32_t const subtype_buffer_size) noexcept;

#else

#define FUSION_GET_COMPATIBILITY_MULTIPLE_SUBTYPES FALSE

#endif

#define FUSION_GET_EXTENSION_INFO
#define FUSION_GET_EXTENSION_INFO_FAILURE FALSE
#define FUSION_GET_EXTENSION_INFO_SUCCESS TRUE
std::int16_t FUSION_API GetRunObjectInfos(mv *const mV, kpxRunInfos *const run_info) noexcept;

#define FUSION_GET_DEPENDENCIES
fusion::string_array_view FUSION_API GetDependencies() noexcept;

#define FUSION_LOAD_OBJECT
#define FUSION_LOAD_OBJECT_FAILURE -1
#define FUSION_LOAD_OBJECT_SUCCESS 0
std::int32_t FUSION_API LoadObject(mv *const mV, fusion::string_view const filename, SerializedEditData *serialized_edit_data, std::int32_t const reserved) noexcept;

#define FUSION_UNLOAD_OBJECT
void FUSION_API UnloadObject(mv *const mV, SerializedEditData *serialized_edit_data, std::int32_t const reserved) noexcept;

#define FUSION_UPDATE_SERIALIZED_EDITDATA
#define FUSION_UPDATE_SERIALIZED_EDITDATA_NO_CHANGES 0
HGLOBAL FUSION_API UpdateEditStructure(mv *const mV, void const *const old_serialized_edit_data) noexcept;

#define FUSION_UPDATE_FILENAMES
void FUSION_API UpdateFileNames(mv *const mV, fusion::string_view const app_name, SerializedEditData *serialized_edit_data,
	void (FUSION_API *update_function)(fusion::string_view const app_name, fusion::string_buffer const file_path_buffer/*_MAX_PATH*/)
) noexcept;

#define FUSION_ENUMERATE_HANDLES
#define FUSION_ENUMERATE_HANDLES_SUCCESS 0
std::int32_t FUSION_API EnumElts(mv *const mV, SerializedEditData *serialized_edit_data, ENUMELTPROC enum_func, ENUMELTPROC undo_func, LPARAM lp1, LPARAM lp2) noexcept;

// Edittime only

#ifndef FUSION_RUNTIME_ONLY

#define FUSION_GET_EXTENSION_METADATA
void FUSION_API GetObjInfos(mv *const mV, SerializedEditData *serialized_edit_data,
	fusion::string_buffer const extension_name_buffer/*255*/,
	fusion::string_buffer const extension_author_buffer/*255*/,
	fusion::string_buffer const extension_copyright_buffer/*255*/,
	fusion::string_buffer const extension_description_buffer/*1024*/,
	fusion::string_buffer const extension_website_buffer/*255*/
) noexcept;

#define FUSION_GET_HELP_FILE
fusion::string_view FUSION_API GetHelpFileName() noexcept;

#define FUSION_CREATE_OBJECT
#define FUSION_CREATE_OBJECT_FAILURE 1
#define FUSION_CREATE_OBJECT_SUCCESS 0
std::int32_t FUSION_API CreateObject(mv *const mV, LO *const level_object, SerializedEditData *serialized_edit_data) noexcept;

#define FUSION_USES_FILE
#define FUSION_USES_FILE_YES TRUE
#define FUSION_USES_FILE_NO FALSE
fusion::boolean FUSION_API UsesFile(mv *const mV, fusion::string_view const file_path) noexcept;

#define FUSION_CREATE_FROM_FILE
void FUSION_API CreateFromFile(mv *const mV, fusion::string_view const file_path, SerializedEditData *serialized_edit_data) noexcept;

#define FUSION_PUT_OBJECT
void FUSION_API PutObject(mv *const mV, LO *const level_object, SerializedEditData *serialized_edit_data, std::uint16_t const count) noexcept;

#define FUSION_CLONE_OBJECT
void FUSION_API DuplicateObject(mv *const mV, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept;

#define FUSION_REMOVE_OBJECT
void FUSION_API RemoveObject(mv *const mV, LO *const level_object, SerializedEditData *serialized_edit_data, std::uint16_t const count) noexcept;

#define FUSION_EDIT_OBJECT
#define FUSION_EDIT_OBJECT_NO_CHANGES 0
#define FUSION_EDIT_OBJECT_CHANGES_MADE 1
std::int32_t FUSION_API EditObject(mv *const mV, OI *const object_info, LO *const level_object, SerializedEditData *serialized_edit_data) noexcept;

#define FUSION_SET_EDIT_SIZE
#define FUSION_SET_EDIT_SIZE_NOT_CHANGED 0
#define FUSION_SET_EDIT_SIZE_CHANGED 1
std::int32_t FUSION_API SetEditSize(mv *const mV, SerializedEditData *serialized_edit_data, std::int32_t const width, std::int32_t const height) noexcept;

#define FUSION_GET_OBJECT_BOUNDS
void FUSION_API GetObjectRect(mv *const mV, RECT *const rect, LO *const level_object, SerializedEditData *serialized_edit_data) noexcept;

#define FUSION_MAKE_ICON
#define FUSION_MAKE_ICON_FAILURE 1
#define FUSION_MAKE_ICON_SUCCESS 0
std::int32_t FUSION_API MakeIconEx(mv *const mV, cSurface *const icon, fusion::string_buffer const name, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept;

#define FUSION_EDITOR_DISPLAY
void FUSION_API EditorDisplay(mv *const mV, OI *const object_info, LO *const level_object, SerializedEditData *serialized_edit_data, RECT *const bounds) noexcept;

#define FUSION_IS_OBJECT_TRANSPARENT
#define FUSION_IS_OBJECT_TRANSPARENT_OPAQUE FALSE
#define FUSION_IS_OBJECT_TRANSPARENT_TRANSPARENT TRUE
fusion::boolean FUSION_API IsObjTransparent(mv *const mV, OI *const level_object, SerializedEditData *serialized_edit_data, std::int32_t const x, std::int32_t const y) noexcept;

#define FUSION_PREPARE_TO_SAVE
void FUSION_API PrepareToWriteObject(mv *const mV, SerializedEditData *const serialized_edit_data, OI *const object_info) noexcept; //serialized_edit_data is a temporary copy that can't be resized

#define FUSION_GET_FILTERS
#define FUSION_GET_FILTERS_NOT_SUPPORTED FALSE
#define FUSION_GET_FILTERS_SUPPORTED TRUE
fusion::boolean FUSION_API GetFilters(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t flags, void const *const) noexcept;

#define FUSION_PREPARE_FLEX_BUILD
void FUSION_API PrepareFlexBuild(mv *const mV, SerializedEditData *serialized_edit_data, fusion::wstring_view const temp_folder) noexcept;

#define FUSION_GET_ACTION_MENU
#define FUSION_GET_ACTION_MENU_NONE NULL
HMENU FUSION_API GetActionMenu(mv *const mV, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept;

#define FUSION_GET_CONDITION_MENU
#define FUSION_GET_CONDITION_MENU_NONE NULL
HMENU FUSION_API GetConditionMenu(mv *const mV, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept;

#define FUSION_GET_EXPRESSION_MENU
#define FUSION_GET_EXPRESSION_MENU_NONE NULL
HMENU FUSION_API GetExpressionMenu(mv *const mV, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept;

#define FUSION_GET_ACTION_ID_FROM_ACTION_MENU_ID
std::int16_t FUSION_API GetActionCodeFromMenu(mv *const mV, std::int16_t const action_menu_id) noexcept;

#define FUSION_GET_CONDITION_ID_FROM_CONDITION_MENU_ID
std::int16_t FUSION_API GetConditionCodeFromMenu(mv *const mV, std::int16_t const condition_menu_id) noexcept;

#define FUSION_GET_EXPRESSION_ID_FROM_EXPRESSION_MENU_ID
std::int16_t FUSION_API GetExpressionCodeFromMenu(mv *const mV, std::int16_t const expression_menu_id) noexcept;

#define FUSION_GET_ACTION_INFO_ARRAY
fusion::ace_info_array FUSION_API GetActionInfos(mv *const mV, std::int16_t const action_id) noexcept;

#define FUSION_GET_CONDITION_INFO_ARRAY
fusion::ace_info_array FUSION_API GetConditionInfos(mv *const mV, std::int16_t const condition_id) noexcept;

#define FUSION_GET_EXPRESSION_INFO_ARRAY
fusion::ace_info_array FUSION_API GetExpressionInfos(mv *const mV, std::int16_t const expression_id) noexcept;

#define FUSION_GET_ACTION_PARAM_NAME
void FUSION_API GetActionTitle(mv *const mV, std::int16_t const action_id, std::int16_t const param_id, fusion::string_buffer const param_name_buffer, std::int16_t const param_name_buffer_size) noexcept;

#define FUSION_GET_CONDITION_PARAM_NAME
void FUSION_API GetConditionTitle(mv *const mV, std::int16_t const condition_id, std::int16_t const param_id, fusion::string_buffer const param_name_buffer, std::int16_t const param_name_buffer_size) noexcept;

#define FUSION_GET_EXPRESSION_PARAM_NAME
void FUSION_API GetExpressionParam(mv *const mV, std::int16_t const expression_id, std::int16_t const param_id, fusion::string_buffer const param_name_buffer, std::int16_t const param_name_buffer_size) noexcept;

#define FUSION_GET_ACTION_DISPLAY_STRING
void FUSION_API GetActionString(mv *const mV, std::int16_t const action_id, fusion::string_buffer const display_string_buffer, std::int16_t const display_string_buffer_size) noexcept;

#define FUSION_GET_CONDITION_DISPLAY_STRING
void FUSION_API GetConditionString(mv *const mV, std::int16_t const condition_id, fusion::string_buffer const display_string_buffer, std::int16_t const display_string_buffer_size) noexcept;

#define FUSION_GET_EXPRESSION_EDITOR_STRING
void FUSION_API GetExpressionString(mv *const mV, std::int16_t const expression_id, fusion::string_buffer const editor_string_buffer, std::int16_t const editor_string_buffer_size) noexcept;

#define FUSION_INITIALIZE_CUSTOM_PARAMETER
void FUSION_API InitParameter(mv *const mV, std::int16_t const custom_id, paramExt *const param_data) noexcept;

#define FUSION_EDIT_CUSTOM_PARAMETER
void FUSION_API EditParameter(mv *const mV, std::int16_t const custom_id, paramExt *const param_data) noexcept;

#define FUSION_GET_CUSTOM_PARAMETER_DISPLAY_STRING
void FUSION_API GetParameterString(mv *const mV, std::int16_t const custom_id, paramExt *const param_data, fusion::string_buffer const display_string_buffer, std::int16_t const display_string_buffer_size) noexcept;

#define FUSION_GET_TEXT_CAPABILITIES
std::uint32_t FUSION_API GetTextCaps(mv *const mV, SerializedEditData *serialized_edit_data) noexcept;

#define FUSION_GET_TEXT_FONT
fusion::boolean FUSION_API GetTextFont(mv *const mV, SerializedEditData *serialized_edit_data, LOGFONT *const font, void const *const, std::uint32_t const) noexcept;

#define FUSION_SET_TEXT_FONT
fusion::boolean FUSION_API SetTextFont(mv *const mV, SerializedEditData *serialized_edit_data, LOGFONT const *const font, void const *const) noexcept;

#define FUSION_GET_TEXT_COLOR
COLORREF FUSION_API GetTextClr(mv *const mV, SerializedEditData *serialized_edit_data) noexcept;

#define FUSION_SET_TEXT_COLOR
void FUSION_API SetTextClr(mv *const mV, SerializedEditData *serialized_edit_data, COLORREF const color) noexcept;

#define FUSION_GET_TEXT_ALIGNMENT
std::uint32_t FUSION_API GetTextAlignment(mv *const mV, SerializedEditData *serialized_edit_data) noexcept;

#define FUSION_SET_TEXT_ALIGNMENT
void FUSION_API SetTextAlignment(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const flags) noexcept;

#define FUSION_GET_PROPERTIES
#define FUSION_GET_PROPERTIES_FAILURE FALSE
#define FUSION_GET_PROPERTIES_SUCCESS TRUE
fusion::boolean FUSION_API GetProperties(mv *const mV, SerializedEditData *serialized_edit_data, fusion::boolean const master_item) noexcept;

#define FUSION_GET_PROPERTY_PARAM
std::int32_t FUSION_API GetPropCreateParam(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id) noexcept;

#define FUSION_FREE_PROPERTY_PARAM
void FUSION_API ReleasePropCreateParam(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id, std::int32_t const param) noexcept;

#define FUSION_FREE_PROPERTIES
void FUSION_API ReleaseProperties(mv *const mV, SerializedEditData *serialized_edit_data, fusion::boolean const master_item) noexcept;

#define FUSION_IS_PROPERTY_ENABLED
#define FUSION_IS_PROPERTY_ENABLED_ENABLED TRUE
#define FUSION_IS_PROPERTY_ENABLED_DISABLED FALSE
fusion::boolean FUSION_API IsPropEnabled(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id) noexcept;

#define FUSION_GET_PROPERTY_VALUE
CPropValue *FUSION_API GetPropValue(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id) noexcept;

#define FUSION_GET_PROPERTY_CHECKBOX
#define FUSION_GET_PROPERTY_CHECKBOX_TICKED TRUE
#define FUSION_GET_PROPERTY_CHECKBOX_UNTICKED FALSE
fusion::boolean FUSION_API GetPropCheck(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id) noexcept;

#define FUSION_SET_PROPERTY_VALUE
void FUSION_API SetPropValue(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id, CPropValue *const property_value) noexcept;

#define FUSION_SET_PROPERTY_CHECKBOX
#define FUSION_SET_PROPERTY_CHECKBOX_TICKED TRUE
#define FUSION_SET_PROPERTY_CHECKBOX_UNTICKED FALSE
void FUSION_API SetPropCheck(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id, fusion::boolean const ticked) noexcept;

#define FUSION_PROPERTY_BUTTON_PRESSED
#define FUSION_PROPERTY_BUTTON_PRESSED_NO_REFRESH FALSE
#define FUSION_PROPERTY_BUTTON_PRESSED_DO_REFRESH TRUE
fusion::boolean FUSION_API EditProp(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id) noexcept;

#endif

// Runtime only

#define FUSION_GET_RUNTIME_STRUCTURE_SIZE
std::uint16_t FUSION_API GetRunObjectDataSize(RunHeader *const run_header, SerializedEditData const *const serialized_edit_data) noexcept;

#define FUSION_FINISH_RUNTIME_STRUCTURE_CONSTRUCTION
#define FUSION_FINISH_RUNTIME_STRUCTURE_CONSTRUCTION_FAILURE 1
#define FUSION_FINISH_RUNTIME_STRUCTURE_CONSTRUCTION_SUCCESS 0
std::int16_t FUSION_API CreateRunObject(RunData *const run_data, SerializedEditData const *const serialized_edit_data, createObjectInfo *const create_object_info) noexcept;

#define FUSION_BEGIN_RUNTIME_STRUCTURE_DESTRUCTION
#define FUSION_BEGIN_RUNTIME_STRUCTURE_DESTRUCTION_SUCCESS 0
std::int16_t FUSION_API DestroyRunObject(RunData *const run_data, std::int32_t const fast) noexcept;

#define FUSION_ON_TICK
#define FUSION_ON_TICK_STOP_CALLING REFLAG_ONESHOT
#define FUSION_ON_TICK_DONT_DRAW 0
#define FUSION_ON_TICK_CALL_DRAW REFLAG_DISPLAY
std::int16_t FUSION_API HandleRunObject(RunData *const run_data) noexcept;

#ifdef FUSION_CUSTOM_RUNTIME_DISPLAY

#ifdef FUSION_MANUAL_INK_EFFECTS

#define FUSION_ON_DRAW
#define FUSION_ON_DRAW_SUCCESS 0
std::int16_t FUSION_API DisplayRunObject(RunData *const run_data) noexcept;

#ifdef FUSION_MANUAL_BACKGROUND_SAVING

#define FUSION_STORE_BACKGROUND
#define FUSION_STORE_BACKGROUND_SUCCESS 0
std::int16_t FUSION_API SaveBackground(RunData *const run_data) noexcept;

#define FUSION_RESTORE_BACKGROUND
#define FUSION_RESTORE_BACKGROUND_SUCCESS 0
std::int16_t FUSION_API RestoreBackground(RunData *const run_data) noexcept;

#define FUSION_FREE_STORED_BACKGROUND
#define FUSION_FREE_STORED_BACKGROUND_SUCCESS 0
std::int16_t FUSION_API KillBackground(RunData *const run_data) noexcept;

#endif

#else

#define FUSION_GET_SURFACE
cSurface *FUSION_API GetRunObjectSurface(RunData *const run_data) noexcept;

#endif

#ifdef FUSION_FINE_COLLISIONS

#define FUSION_GET_FINE_COLLISION_MASK
sMask *FUSION_API GetRunObjectCollisionMask(RunData *const run_data, std::int32_t const lparam) noexcept;

#endif

#ifdef FUSION_DRAWS_TEXT

#ifdef FUSION_DRAWS_TEXT_USER_FONT

#define FUSION_GET_TEXT_FONT_RUNTIME
void FUSION_API GetRunObjectFont(RunData *const run_data, LOGFONT *const font) noexcept;

#define FUSION_SET_TEXT_FONT_RUNTIME
void FUSION_API SetRunObjectFont(RunData *const run_data, LOGFONT const *const font, RECT const *const new_size) noexcept;

#endif

#ifdef FUSION_DRAWS_TEXT_USER_COLOR

#define FUSION_GET_TEXT_COLOR_RUNTIME
COLORREF FUSION_API GetRunObjectTextColor(RunData *const run_data) noexcept;

#define FUSION_SET_TEXT_COLOR_RUNTIME
void FUSION_API SetRunObjectTextColor(RunData *const run_data, COLORREF const color) noexcept;

#endif

#endif

#endif

#define FUSION_PAUSE_RUNTIME
#define FUSION_PAUSE_RUNTIME_SUCCESS 0
std::int16_t FUSION_API PauseRunObject(RunData *const run_data) noexcept;

#define FUSION_UNPAUSE_RUNTIME
#define FUSION_UNPAUSE_RUNTIME_SUCCESS 0
std::int16_t FUSION_API ContinueRunObject(RunData *const run_data) noexcept;

#define FUSION_SERIALIZE_RUNTIME
#define FUSION_SERIALIZE_RUNTIME_FAILURE FALSE
#define FUSION_SERIALIZE_RUNTIME_SUCCESS TRUE
fusion::boolean FUSION_API SaveRunObject(RunData *const run_data, HANDLE const file_handle) noexcept;

#define FUSION_DESERIALIZE_RUNTIME
#define FUSION_DESERIALIZE_RUNTIME_FAILURE FALSE
#define FUSION_DESERIALIZE_RUNTIME_SUCCESS TRUE
fusion::boolean FUSION_API LoadRunObject(RunData *const run_data, HANDLE const file_handle) noexcept;

#define FUSION_START_APPLICATION
void FUSION_API StartApp(mv *const mV, CRunApp *const app) noexcept;

#define FUSION_END_APPLICATION
void FUSION_API EndApp(mv *const mV, CRunApp *const app) noexcept;

#define FUSION_START_FRAME
void FUSION_API StartFrame(mv *const mV, CRunApp *const app, std::int32_t const frame_index) noexcept;

#define FUSION_END_FRAME
void FUSION_API EndFrame(mv *const mV, CRunApp *const app, std::int32_t const frame_index) noexcept;

#ifdef FUSION_CUSTOM_WINDOW_PROC

#define FUSION_WINDOW_PROC
LRESULT CALLBACK WindowProc(RunHeader *const run_header, HWND const window, UINT const message_type, WPARAM const wParam, LPARAM const lParam) noexcept;

#endif

#ifdef FUSION_CUSTOM_DEBUGGER

#ifndef FUSION_RUNTIME_ONLY

#define FUSION_GET_DEBUG_ITEMS
fusion::debug_item_array FUSION_API GetDebugTree(RunData *const run_data) noexcept;

#define FUSION_GET_DEBUG_ITEM_STRING
void FUSION_API GetDebugItem(fusion::string_buffer const buffer, RunData *const run_data, std::int32_t const id) noexcept;

#define FUSION_EDIT_DEBUG_ITEM
void FUSION_API EditDebugItem(RunData *const run_data, std::int32_t const id) noexcept;

#endif

#endif

#define FUSION_ACTIONS

#define FUSION_CONDITIONS
#define FUSION_CONDITIONS_FALSE 0
#define FUSION_CONDITIONS_TRUE 1

#define FUSION_EXPRESSIONS

#endif
