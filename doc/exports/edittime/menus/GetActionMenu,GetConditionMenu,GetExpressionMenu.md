Called every time the user right-clicks to get the menu in the event editor.
```cpp
#ifdef FUSION_GET_ACTION_MENU
auto FUSION_API GetActionMenu(mv *const mV, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept
-> HMENU
```
```cpp
#ifdef FUSION_GET_CONDITION_MENU
auto FUSION_API GetConditionMenu(mv *const mV, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept
-> HMENU
```
```cpp
#ifdef FUSION_GET_EXPRESSION_MENU
auto FUSION_API GetExpressionMenu(mv *const mV, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept
-> HMENU
```
When you return an `HMENU` you transfer ownership of it to Fusion, and thus Fusion will eventually call `DestroyMenu` on it.
You can use the helper class in `#include "lSDK/FusionMenu.hpp` to generate the menu as shown in the example project.
You should have a separator at the start and the end of each menu, otherwise your menu items will blend together with the inbuilt ones.

The data value of each menu item is important and must be between `FUSION_MENU_*IONS_FIRST` and `FUSION_MENU_*IONS_LAST`, inclusive.
The range is different for each type of menu (actions/conditions/expressions).
If the data value is not within the correct range, Fusion will ignore the menu item and it will not be displayed.

When the user clicks on a menu item in the aforementioned range, Fusion will pass the data value to `Get*ionCodeFromMenu`.
If you will have less than 1000 actions/conditions/expressions, you can simply store the relevant ID directly in the data value (adjusted to be within the correct range).
Otherwise you are free to store any value that will be useful in `Get*ionCodeFromMenu` later.
