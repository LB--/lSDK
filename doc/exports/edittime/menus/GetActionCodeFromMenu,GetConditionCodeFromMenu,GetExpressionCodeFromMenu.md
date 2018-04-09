Called once the user has selected one of your menu items.
You should read the documentation for `Get*ionMenu` first.
```cpp
#ifdef FUSION_GET_ACTION_ID_FROM_ACTION_MENU_ID
auto FUSION_API GetActionCodeFromMenu(mv *const mV, std::int16_t const action_menu_id) noexcept
-> std::int16_t
```
```cpp
#ifdef FUSION_GET_CONDITION_ID_FROM_CONDITION_MENU_ID
auto FUSION_API GetConditionCodeFromMenu(mv *const mV, std::int16_t const condition_menu_id) noexcept
-> std::int16_t
```
```cpp
#ifdef FUSION_GET_EXPRESSION_ID_FROM_EXPRESSION_MENU_ID
auto FUSION_API GetExpressionCodeFromMenu(mv *const mV, std::int16_t const expression_menu_id) noexcept
-> std::int16_t
```
If you stored the action/condition/expression ID directly, you can just subtract the start of the range from the given menu data value.
Otherwise, you may want to open a dialog or menu of some sort based on the given menu data value and let the user pick from more options that then result in an ACE ID.
Some extensions use this to get around the 1000 menu item limit.

There is no way to return any value that indicates "nevermind" or "cancel" - you must return a valid ID.

You must export these functions if you export their corresponding `Get*ionMenu` functions.
