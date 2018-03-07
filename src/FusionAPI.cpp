#include "FusionAPI.hpp"

using pointer = void const *const;
static_assert(sizeof(pointer) == 4);

using i16 = std::int16_t const;
using i32 = std::int32_t const;

HINSTANCE fusion::DLL = 0;
#ifdef FUSION_NO_DLL_MAIN
BOOL WINAPI DllMain(HINSTANCE dll, DWORD reason, LPVOID reserved) noexcept
{
	if(reason == DLL_PROCESS_ATTACH)
	{
		fusion::DLL = dll;
	}
	return TRUE;
}
#endif

#ifdef FUSION_NO_INITIALIZE
auto FUSION_API InitExt(mv *const, std::int32_t const) noexcept
-> std::int32_t
{
	return FUSION_INITIALIZE_SUCCESS;
}
#endif

#ifdef FUSION_NO_FREE
auto FUSION_API FreeExt(mv *const) noexcept
-> std::int32_t
{
	return FUSION_FREE_SUCCESS;
}
#endif

#ifdef FUSION_NO_GET_DEPENDENCIES
auto FUSION_API GetDependencies() noexcept
-> fusion::string_array_view
{
	return nullptr;
}
#endif

#ifdef FUSION_NO_LOAD_OBJECT
auto FUSION_API LoadObject(mv *const, fusion::string_view const, SerializedEditData *, std::int32_t const) noexcept
-> std::int32_t
{
	return FUSION_LOAD_OBJECT_SUCCESS;
}
#endif

#ifdef FUSION_NO_UNLOAD_OBJECT
void FUSION_API UnloadObject(mv *const, SerializedEditData *, std::int32_t const) noexcept
{
}
#endif

#ifdef FUSION_NO_UPDATE_SERIALIZED_EDITDATA
auto FUSION_API UpdateEditStructure(mv *const, void const *const) noexcept
-> HGLOBAL
{
	return FUSION_UPDATE_SERIALIZED_EDITDATA_NO_CHANGES;
}
#endif

#ifdef FUSION_NO_UPDATE_FILENAMES
void FUSION_API UpdateFileNames(mv *const, fusion::string_view const, SerializedEditData *,
	void (FUSION_API *)(fusion::string_view const, fusion::string_buffer const)
) noexcept
{
}
#endif

#ifdef FUSION_NO_ENUMERATE_HANDLES
auto FUSION_API EnumElts(mv *const, SerializedEditData *, ENUMELTPROC, ENUMELTPROC, LPARAM, LPARAM) noexcept
-> std::int32_t
{
	return FUSION_ENUMERATE_HANDLES_SUCCESS;
}
#endif

#ifndef FUSION_GET_EXTENSION_METADATA
void FUSION_API GetObjInfos(pointer, pointer, pointer, pointer, pointer, pointer, pointer) noexcept
{
}
#endif

#ifndef FUSION_GET_HELP_FILE
auto FUSION_API GetHelpFileName() noexcept
-> pointer
{
	return nullptr;
}
#endif

#ifndef FUSION_CREATE_OBJECT
auto FUSION_API CreateObject(pointer, pointer, pointer) noexcept
-> i32
{
	return 0;
}
#else
#ifdef FUSION_NO_CREATE_OBJECT
auto FUSION_API CreateObject(mv *const, LO *const, SerializedEditData *) noexcept
-> std::int32_t
{
	return FUSION_CREATE_OBJECT_SUCCESS;
}
#endif
#endif

#ifndef FUSION_USES_FILE
auto FUSION_API UsesFile(pointer, pointer) noexcept
-> i32
{
	return 0;
}
#else
#ifdef FUSION_NO_USES_FILE
auto FUSION_API UsesFile(mv *const, fusion::string_view const) noexcept
-> fusion::boolean
{
	return FUSION_USES_FILE_NO;
}
#endif
#endif

#ifndef FUSION_CREATE_FROM_FILE
void FUSION_API CreateFromFile(pointer, pointer, pointer) noexcept
{
}
#else
#ifdef FUSION_NO_CREATE_FROM_FILE
void FUSION_API CreateFromFile(mv *const, fusion::string_view const, SerializedEditData *) noexcept
{
}
#endif
#endif

#ifndef FUSION_PUT_OBJECT
void FUSION_API PutObject(pointer, pointer, pointer, i16) noexcept
{
}
#else
#ifdef FUSION_NO_PUT_OBJECT
void FUSION_API PutObject(mv *const, LO *const, SerializedEditData *, std::uint16_t const) noexcept
{
}
#endif
#endif

#ifndef FUSION_CLONE_OBJECT
void FUSION_API DuplicateObject(pointer, pointer, pointer) noexcept
{
}
#else
#ifdef FUSION_NO_CLONE_OBJECT
void FUSION_API DuplicateObject(mv *const, OI *const, SerializedEditData *) noexcept
{
}
#endif
#endif

#ifndef FUSION_REMOVE_OBJECT
void FUSION_API RemoveObject(pointer, pointer, pointer, i16) noexcept
{
}
#else
#ifdef FUSION_NO_REMOVE_OBJECT
void FUSION_API RemoveObject(mv *const, LO *const, SerializedEditData *, std::uint16_t const) noexcept
{
}
#endif
#endif

#ifndef FUSION_EDIT_OBJECT
auto FUSION_API EditObject(pointer, pointer, pointer, pointer) noexcept
-> i32
{
}
#else
#ifdef FUSION_NO_EDIT_OBJECT
auto FUSION_API EditObject(mv *const, OI *const, LO *const, SerializedEditData *) noexcept
-> std::int32_t
{
	return FUSION_EDIT_OBJECT_NO_CHANGES;
}
#endif
#endif

#ifdef FUSION_RESIZABLE_OBJECT
#ifndef FUSION_SET_EDIT_SIZE
auto FUSION_API SetEditSize(pointer, pointer, i32, i32) noexcept
-> i32
{
	return 0;
}
#endif
#endif

#ifndef FUSION_GET_OBJECT_BOUNDS
void FUSION_API GetObjectRect(pointer, pointer, pointer, pointer) noexcept
{
}
#else
#ifdef FUSION_NO_GET_OBJECT_BOUNDS
void FUSION_API GetObjectRect(mv *const, RECT *const rect, LO *const, SerializedEditData *) noexcept
{
	if(rect)
	{
		rect->right = rect->left + 32; //w
		rect->bottom = rect->top + 32; //h
	}
}
#endif
#endif

#ifdef FUSION_CUSTOM_ICON
#ifdef FUSION_NO_MAKE_ICON
auto FUSION_API MakeIconEx(mv *const, cSurface *const icon, fusion::string_buffer const, OI *const, SerializedEditData *) noexcept
-> std::int32_t
{
	if(icon && icon->LoadImage(fusion::DLL, EXO_ICON))
	{
		return FUSION_MAKE_ICON_SUCCESS;
	}
	return FUSION_MAKE_ICON_FAILURE;
}
#endif
#endif

#ifdef FUSION_EDITOR_DISPLAY
#ifdef FUSION_NO_EDITOR_DISPLAY
void FUSION_API EditorDisplay(mv *const mV, OI *const, LO *const, SerializedEditData *, RECT *const bounds) noexcept
{
	if(!mV || !bounds)
	{
		return;
	}
	cSurface *frame_window = WinGetSurface(reinterpret_cast<std::int32_t>(mV->mvIdEditWin));
	if(!frame_window)
	{
		return;
	}
	cSurface *prototype = nullptr;
	if(!GetSurfacePrototype(&prototype, 32, ST_MEMORY, SD_DIB))
	{
		return
	}
	cSurface icon;
	icon.Create(32, 32, prototype);
	if(!icon.LoadImage(fusion::DLL, EXO_ICON, LI_REMAP))
	{
		return;
	}
	if(!icon.Blit(*frame_window, bounds->left, bounds->top, BMODE_TRANSP, BOP_COPY))
	{
		return;
	}
}
#endif
#endif

#ifndef FUSION_IS_OBJECT_TRANSPARENT
auto FUSION_API IsObjTransparent(pointer, pointer, pointer, i32, i32) noexcept
-> i32
{
	return 0;
}
#else
#ifdef FUSION_NO_IS_OBJECT_TRANSPARENT
auto FUSION_API IsObjTransparent(mv *const, OI *const, SerializedEditData *, std::int32_t const, std::int32_t const) noexcept
-> fusion::boolean
{
	return FUSION_IS_OBJECT_TRANSPARENT_OPAQUE;
}
#endif
#endif

#ifndef FUSION_PREPARE_TO_SAVE
void FUSION_API PrepareToWriteObject(pointer, pointer, pointer) noexcept
{
}
#else
#ifdef FUSION_NO_PREPARE_TO_SAVE
void FUSION_API PrepareToWriteObject(mv *const, SerializedEditData *const, OI *const) noexcept
{
}
#endif
#endif

#ifdef FUSION_CUSTOM_FILTERS
#ifndef FUSION_GET_FILTERS
auto FUSION_API GetFilters(pointer, pointer, i32, pointer) noexcept
-> i32
{
	return 0;
}
#endif
#endif

#ifdef FUSION_CUSTOM_FLEX_BUILD
#ifndef FUSION_PREPARE_FLEX_BUILD
void FUSION_API PrepareFlexBuild(pointer, pointer, pointer) noexcept
{
}
#endif
#endif

#ifndef FUSION_GET_ACTION_MENU
auto FUSION_API GetActionMenu(pointer, pointer, pointer) noexcept
-> pointer
{
	return nullptr;
}
#else
#ifdef FUSION_NO_GET_ACTION_MENU
auto FUSION_API GetActionMenu(mv *const, OI *const, SerializedEditData *) noexcept
-> HMENU
{
	return FUSION_GET_ACTION_MENU_NONE;
}
#endif
#endif

#ifndef FUSION_GET_CONDITION_MENU
auto FUSION_API GetConditionMenu(pointer, pointer, pointer) noexcept
-> pointer
{
	return nullptr;
}
#else
#ifdef FUSION_NO_GET_CONDITION_MENU
auto FUSION_API GetConditionMenu(mv *const, OI *const, SerializedEditData *) noexcept
-> HMENU
{
	return FUSION_GET_CONDITION_MENU_NONE;
}
#endif
#endif

#ifndef FUSION_GET_EXPRESSION_MENU
auto FUSION_API GetExpressionMenu(pointer, pointer, pointer) noexcept
-> pointer
{
	return nullptr;
}
#else
#ifdef FUSION_NO_GET_EXPRESSION_MENU
auto FUSION_API GetExpressionMenu(mv *const, OI *const, SerializedEditData *) noexcept
-> HMENU
{
	return FUSION_GET_EXPRESSION_MENU_NONE;
}
#endif
#endif

#ifndef FUSION_GET_ACTION_ID_FROM_ACTION_MENU_ID
auto FUSION_API GetActionCodeFromMenu(pointer, i16) noexcept
-> i16
{
	return 0;
}
#else
#ifdef FUSION_NO_GET_ACTION_ID_FROM_ACTION_MENU_ID
auto FUSION_API GetActionCodeFromMenu(mv *const, std::int16_t const action_menu_id) noexcept
-> std::int16_t
{
	return action_menu_id - FUSION_MENU_ACTIONS_FIRST;
}
#endif
#endif

#ifndef FUSION_GET_CONDITION_ID_FROM_CONDITION_MENU_ID
auto FUSION_API GetConditionCodeFromMenu(pointer, i16) noexcept
-> i16
{
	return 0;
}
#else
#ifdef FUSION_NO_GET_CONDITION_ID_FROM_CONDITION_MENU_ID
auto FUSION_API GetConditionCodeFromMenu(mv *const, std::int16_t const condition_menu_id) noexcept
-> std::int16_t
{
	return condition_menu_id - FUSION_MENU_CONDITIONS_FIRST;
}
#endif
#endif

#ifndef FUSION_GET_EXPRESSION_ID_FROM_EXPRESSION_MENU_ID
auto FUSION_API GetExpressionCodeFromMenu(pointer, i16) noexcept
-> i16
{
	return 0;
}
#else
#ifdef FUSION_NO_GET_EXPRESSION_ID_FROM_EXPRESSION_MENU_ID
auto FUSION_API GetExpressionCodeFromMenu(mv *const, std::int16_t const expression_menu_id) noexcept
-> std::int16_t
{
	return expression_menu_id - FUSION_MENU_EXPRESSIONS_FIRST;
}
#endif
#endif

#ifndef FUSION_GET_ACTION_INFO_ARRAY
auto FUSION_API GetActionInfos(pointer, i16) noexcept
-> pointer
{
	return nullptr;
}
#endif

#ifndef FUSION_GET_CONDITION_INFO_ARRAY
auto FUSION_API GetConditionInfos(pointer, i16) noexcept
-> pointer
{
	return nullptr;
}
#endif

#ifndef FUSION_GET_EXPRESSION_INFO_ARRAY
auto FUSION_API GetExpressionInfos(pointer, i16) noexcept
-> pointer
{
	return nullptr;
}
#endif

#ifndef FUSION_GET_ACTION_PARAM_NAME
void FUSION_API GetActionTitle(pointer, i16, i16, pointer, i16) noexcept
{
}
#endif

#ifndef FUSION_GET_CONDITION_PARAM_NAME
void FUSION_API GetConditionTitle(pointer, i16, i16, pointer, i16) noexcept
{
}
#endif

#ifndef FUSION_GET_EXPRESSION_PARAM_NAME
void FUSION_API GetExpressionParam(pointer, i16, i16, pointer, i16) noexcept
{
}
#endif

#ifndef FUSION_GET_ACTION_DISPLAY_STRING
void FUSION_API GetActionString(pointer, i16, pointer, i16) noexcept
{
}
#endif

#ifndef FUSION_GET_CONDITION_DISPLAY_STRING
void FUSION_API GetConditionString(pointer, i16, pointer, i16) noexcept
{
}
#endif

#ifndef FUSION_GET_EXPRESSION_EDITOR_STRING
void FUSION_API GetExpressionString(pointer, i16, pointer, i16) noexcept
{
}
#endif

#ifndef FUSION_INITIALIZE_CUSTOM_PARAMETER
void FUSION_API InitParameter(pointer, i16, pointer) noexcept
{
}
#endif

#ifndef FUSION_EDIT_CUSTOM_PARAMETER
void FUSION_API EditParameter(pointer, i16, pointer) noexcept
{
}
#endif

#ifndef FUSION_GET_CUSTOM_PARAMETER_DISPLAY_STRING
void FUSION_API GetParameterString(pointer, i16, pointer, pointer, i16) noexcept
{
}
#endif

#ifndef FUSION_GET_TEXT_CAPABILITIES
auto FUSION_API GetTextCaps(pointer, pointer) noexcept
-> i32
{
	return 0;
}
#endif

#ifndef FUSION_GET_TEXT_FONT
auto FUSION_API GetTextFont(pointer, pointer, pointer, pointer, i32) noexcept
-> i32
{
	return 0;
}
#endif

#ifndef FUSION_SET_TEXT_FONT
auto FUSION_API SetTextFont(pointer, pointer, pointer, pointer) noexcept
-> i32
{
	return 0;
}
#endif

#ifndef FUSION_GET_TEXT_COLOR
auto FUSION_API GetTextClr(pointer, pointer) noexcept
-> i32
{
	return 0;
}
#endif

#ifndef FUSION_SET_TEXT_COLOR
void FUSION_API SetTextClr(pointer, pointer, i32) noexcept
{
}
#endif

#ifndef FUSION_GET_TEXT_ALIGNMENT
auto FUSION_API GetTextAlignment(pointer, pointer) noexcept
-> i32
{
	return 0;
}
#endif

#ifndef FUSION_SET_TEXT_ALIGNMENT
void FUSION_API SetTextAlignment(pointer, pointer, i32) noexcept
{
}
#endif

#ifndef FUSION_GET_PROPERTIES
auto FUSION_API GetProperties(pointer, pointer, i32) noexcept
-> i32
{
	return 0;
}
#endif

#ifndef FUSION_GET_PROPERTY_PARAM
auto FUSION_API GetPropCreateParam(pointer, pointer, i32) noexcept
-> i32
{
	return 0;
}
#else
#ifdef FUSION_NO_GET_PROPERTY_PARAM
auto FUSION_API GetPropCreateParam(mv *const, SerializedEditData *, std::uint32_t const) noexcept
-> std::int32_t
{
	return 0;
}
#endif
#endif

#ifndef FUSION_FREE_PROPERTY_PARAM
void FUSION_API ReleasePropCreateParam(pointer, pointer, i32, i32) noexcept
{
}
#else
#ifdef FUSION_NO_FREE_PROPERTY_PARAM
void FUSION_API ReleasePropCreateParam(mv *const, SerializedEditData *, std::uint32_t const, std::int32_t const) noexcept
{
}
#endif
#endif

#ifndef FUSION_FREE_PROPERTIES
void FUSION_API ReleaseProperties(pointer, pointer, i32) noexcept
{
}
#else
#ifdef FUSION_NO_FREE_PROPERTIES
void FUSION_API ReleaseProperties(mv *const, SerializedEditData *, fusion::boolean const) noexcept
{
}
#endif
#endif

#ifndef FUSION_IS_PROPERTY_ENABLED
auto FUSION_API IsPropEnabled(pointer, pointer, i32) noexcept
-> i32
{
}
#else
#ifdef FUSION_NO_IS_PROPERTY_ENABLED
auto FUSION_API IsPropEnabled(mv *const, SerializedEditData *, std::uint32_t const) noexcept
-> fusion::boolean
{
	return FUSION_IS_PROPERTY_ENABLED_ENABLED;
}
#endif
#endif

#ifndef FUSION_GET_PROPERTY_VALUE
auto FUSION_API GetPropValue(pointer, pointer, i32) noexcept
-> pointer
{
	return nullptr;
}
#else
#ifdef FUSION_NO_GET_PROPERTY_VALUE
auto FUSION_API GetPropValue(mv *const, SerializedEditData *, std::uint32_t const) noexcept
-> CPropValue *
{
	return nullptr;
}
#endif
#endif

#ifndef FUSION_GET_PROPERTY_CHECKBOX
auto FUSION_API GetPropCheck(pointer, pointer, i32) noexcept
-> i32
{
	return 0;
}
#else
#ifdef FUSION_NO_GET_PROPERTY_CHECKBOX
auto FUSION_API GetPropCheck(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id) noexcept
-> fusion::boolean
{
	return FUSION_GET_PROPERTY_CHECKBOX_UNTICKED;
}
#endif
#endif

#ifndef FUSION_SET_PROPERTY_VALUE
void FUSION_API SetPropValue(pointer, pointer, i32, pointer) noexcept
{
}
#else
#ifdef FUSION_NO_SET_PROPERTY_VALUE
void FUSION_API SetPropValue(mv *const, SerializedEditData *, std::uint32_t const, CPropValue *const) noexcept
{
}
#endif
#endif

#ifndef FUSION_SET_PROPERTY_CHECKBOX
void FUSION_API SetPropCheck(pointer, pointer, i32, i32) noexcept
{
}
#else
#ifdef FUSION_NO_SET_PROPERTY_CHECKBOX
void FUSION_API SetPropCheck(mv *const, SerializedEditData *, std::uint32_t const, fusion::boolean const) noexcept
{
}
#endif
#endif

#ifndef FUSION_PROPERTY_BUTTON_PRESSED
auto FUSION_API EditProp(pointer, pointer, i32) noexcept
-> i32
{
	return 0;
}
#else
#ifdef FUSION_NO_PROPERTY_BUTTON_PRESSED
auto FUSION_API EditProp(mv *const, SerializedEditData *, std::uint32_t const) noexcept
-> fusion::boolean
{
	return FUSION_PROPERTY_BUTTON_PRESSED_NO_REFRESH;
}
#endif
#endif

#ifndef FUSION_GET_RUNTIME_STRUCTURE_SIZE
auto FUSION_API GetRunObjectDataSize(pointer, pointer) noexcept
-> i16
{
	return 0;
}
#endif

#ifndef FUSION_FINISH_RUNTIME_STRUCTURE_CONSTRUCTION
auto FUSION_API CreateRunObject(pointer, pointer, pointer) noexcept
-> i16
{
	return 1;
}
#endif

#ifndef FUSION_BEGIN_RUNTIME_STRUCTURE_DESTRUCTION
auto FUSION_API DestroyRunObject(pointer, i32) noexcept
-> i16
{
	return 1;
}
#endif

#ifndef FUSION_ON_TICK
auto FUSION_API HandleRunObject(pointer) noexcept
-> i16
{
#ifdef REFLAG_ONESHOT
	return REFLAG_ONESHOT;
#else
	return 1;
#endif
}
#else
#ifdef FUSION_NO_ON_TICK
auto FUSION_API HandleRunObject(RunData *const run_data) noexcept
-> std::int16_t
{
#ifdef FUSION_CUSTOM_RUNTIME_DISPLAY
	return FUSION_ON_TICK_CALL_DRAW;
#else
	return FUSION_ON_TICK_DONT_DRAW;
#endif
}
#endif
#endif

#ifndef FUSION_ON_DRAW
auto FUSION_API DisplayRunObject(pointer) noexcept
-> i16
{
	return 0;
}
#endif

#ifndef FUSION_GET_SURFACE
auto FUSION_API GetRunObjectSurface(pointer) noexcept
-> pointer
{
	return nullptr;
}
#endif

#ifndef FUSION_GET_FINE_COLLISION_MASK
auto FUSION_API GetRunObjectCollisionMask(pointer, i32) noexcept
-> pointer
{
	return nullptr;
}
#endif

#ifndef FUSION_STORE_BACKGROUND
auto FUSION_API SaveBackground(pointer) noexcept
-> i16
{
	return 0;
}
#endif

#ifndef FUSION_RESTORE_BACKGROUND
auto FUSION_API RestoreBackground(pointer) noexcept
-> i16
{
	return 0;
}
#endif

#ifndef FUSION_FREE_STORED_BACKGROUND
auto FUSION_API KillBackground(pointer) noexcept
-> i16
{
	return 0;
}
#endif

#ifndef FUSION_GET_TEXT_FONT_RUNTIME
void FUSION_API GetRunObjectFont(pointer, pointer) noexcept
{
}
#endif

#ifndef FUSION_SET_TEXT_FONT_RUNTIME
void FUSION_API SetRunObjectFont(pointer, pointer, pointer) noexcept
{
}
#endif

#ifndef FUSION_GET_TEXT_COLOR_RUNTIME
auto FUSION_API GetRunObjectTextColor(pointer) noexcept
-> i32
{
	return 0;
}
#endif

#ifndef FUSION_SET_TEXT_COLOR_RUNTIME
void FUSION_API SetRunObjectTextColor(pointer, i32) noexcept
{
}
#endif

#ifndef FUSION_PAUSE_RUNTIME
auto FUSION_API PauseRunObject(pointer) noexcept
-> i16
{
	return 0;
}
#else
#ifdef FUSION_NO_PAUSE_RUNTIME
auto FUSION_API PauseRunObject(RunData *const) noexcept
-> std::int16_t
{
	return FUSION_PAUSE_RUNTIME_SUCCESS;
}
#endif
#endif

#ifndef FUSION_UNPAUSE_RUNTIME
auto FUSION_API ContinueRunObject(pointer) noexcept
-> i16
{
	return 0;
}
#else
#ifdef FUSION_NO_UNPAUSE_RUNTIME
auto FUSION_API ContinueRunObject(RunData *const) noexcept
-> std::int16_t
{
	return FUSION_UNPAUSE_RUNTIME_SUCCESS;
}
#endif
#endif

#ifndef FUSION_SERIALIZE_RUNTIME
auto FUSION_API SaveRunObject(pointer, pointer) noexcept
-> i32
{
	return 0;
}
#endif

#ifndef FUSION_DESERIALIZE_RUNTIME
auto FUSION_API LoadRunObject(pointer, pointer) noexcept
-> i32
{
	return 0;
}
#endif

#ifndef FUSION_START_APPLICATION
void FUSION_API StartApp(pointer, pointer) noexcept
{
}
#else
#ifdef FUSION_NO_START_APPLICATION
void FUSION_API StartApp(mv *const, CRunApp *const) noexcept
{
}
#endif
#endif

#ifndef FUSION_END_APPLICATION
void FUSION_API EndApp(pointer, pointer) noexcept
{
}
#else
#ifdef FUSION_NO_END_APPLICATION
void FUSION_API EndApp(pointer, pointer) noexcept
{
}
#endif
#endif

#ifndef FUSION_START_FRAME
void FUSION_API StartFrame(pointer, pointer, i32) noexcept
{
}
#endif

#ifndef FUSION_END_FRAME
void FUSION_API EndFrame(pointer, pointer, i32) noexcept
{
}
#endif

#ifndef FUSION_GET_DEBUG_ITEMS
auto FUSION_API GetDebugTree(pointer) noexcept
-> pointer
{
	return nullptr;
}
#endif

#ifndef FUSION_GET_DEBUG_ITEM_STRING
void FUSION_API GetDebugItem(pointer, pointer, i32) noexcept
{
}
#endif

#ifndef FUSION_EDIT_DEBUG_ITEM
void FUSION_API EditDebugItem(pointer, i32) noexcept
{
}
#endif
