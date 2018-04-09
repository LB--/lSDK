These functions inform Fusion about the parameter types and properties of actions/conditions/expressions.
```cpp
#ifdef FUSION_GET_ACTION_INFO_ARRAY
auto FUSION_API GetActionInfos(mv *const mV, std::int16_t const action_id) noexcept
-> fusion::ace_info_array
```
```cpp
#ifdef FUSION_GET_CONDITION_INFO_ARRAY
auto FUSION_API GetConditionInfos(mv *const mV, std::int16_t const condition_id) noexcept
-> fusion::ace_info_array
```
```cpp
#ifdef FUSION_GET_EXPRESSION_INFO_ARRAY
auto FUSION_API GetExpressionInfos(mv *const mV, std::int16_t const expression_id) noexcept
-> fusion::ace_info_array
```
The array you return must remain valid until Fusion asks for the same ID again.
You can use `lSDK::constant_ace_info<>()` from `#include "lSDK/FusionUtilities.hpp"` for making a static array.

Keep in mind that `GetExpressionInfos` is called continuously while the expression editor is open, as Fusion constantly checks to see if the expression is valid.

You must export these functions if you export their corresponding `Get*ionMenu` functions.

## Array content

The contents of the array are as follows:
* The first element must be the ID of the action/condition/expression (it should match the given parameter)
* The second element is a set of optional flags detailed in the sections below
* The third element is the number of parameters, henceforth referred to as `num`
* The next `num` elements are the parameter types as detailed in the sections below
* The next `num` elements should be `0`, these are required for compatibility reasons. Previously these were resource identifiers to the strings in the resource file.

### Action flags
While there do appear to be some flags for actions in Fusion's headers, they are not documented and you will not need to use them.

### Condition flags
* `EVFLAGS_ALWAYS` means the condition is not a triggered condition
* `EVFLAGS_NOTABLE` means the user can negate the condition, you should always provide this flag unless you have good reason not to (such as manipulating the selected object list)

### Expression flags
By default, an expression is assumed to return an integer or float.
Specifying `EXPFLAG_STRING` means the expression instead returns a string.

### Parameter types
The following parameter types are valid for actions and conditions:
* `PARAM_EXPRESSION` (int32 or float or double) - a number
* `PARAM_EXPSTRING` (pointer to string) - a string
* `PARAM_TIME` (int32) - a time value measured in milliseconds
* `PARAM_PLAYER` (int32) - a player number from 0 to 3
* `PARAM_KEY` (int32) - a Windows virtual key code
* `PARAM_SPEED` (int32) - a speed value
* `PARAM_POSITION` (int32) - X and Y values passed as 16-bit values inside a 32-bit integer, with the X value occupying the most significant bytes
* `PARAM_JOYDIRECTION` (int32) - contains flags `JOYSTICK_*` for directions and fire buttons
* `PARAM_ZONE` (pointer to array) - a zone on the frame area, the array consists of four 16-bit signed integers: left, top, right, bottom
* `PARAM_COLOUR` (int32) - an RGB color
* `PARAM_NEWDIRECTION` (int32) - each bit represents whether that direction has been chosen from the set of 32 directions, with the least significant bit being east and each more significant bit going counter-clockwise
* `PARAM_CLICK` (int32) - least significant byte is 0 for left click, 1 for middle click, or 2 for right click, and `PARAMCLICK_DOUBLE` is masked in if it's supposed to be a double click
* `PARAM_FILENAME` (pointer to string) - deprecated, use `PARAM_FILENAME2` instead
* `PARAM_FILENAME2` (pointer to string) - the parameter name should be in the format `#Title#Choose a file...#Filter#PNG files|*.png|All files|*|`

The following paramater types are only intended to be used by conditions:
* `PARAM_COMPARAISON` - the condition should return an integer for Fusion to perform the comparison
* `PARAM_CMPTIME` - the condition should return an integer time in milliseconds for Fusion to perform the comparison
* `PARAM_CMPSTRING` - the condition should return a pointer to a string for Fusion to perform the comparison

The following action and condition parameter types are also available but only sparsely documented in `Cncf.h`:
* `PARAM_OBJECT`
* `PARAM_BORDER`
* `PARAM_DIRECTION`
* `PARAM_INTEGER`
* `PARAM_SAMPLE`
* `PARAM_MUSIC`
* `PARAM_CREATE`
* `PARAM_ANIMATION`
* `PARAM_NOP`
* `PARAM_EVERY`
* `PARAM_SHOOT`
* `PARAM_SYSCREATE`
* `PARAM_BUFFER4`
* `PARAM_FRAME`
* `PARAM_SAMLOOP`
* `PARAM_MUSLOOP`
* `PARAM_TEXTNUMBER`
* `PARAM_PROGRAM`
* `OLDPARAM_VARGLO`
* `PARAM_CNDSAMPLE`
* `PARAM_CNDMUSIC`
* `PARAM_REMARK`
* `PARAM_GROUP`
* `PARAM_GROUPOINTER`
* `PARAM_STRING`
* `PARAM_PASTE`
* `PARAM_VMKEY`
* `PARAM_INKEFFECT`
* `PARAM_MENU`
* `PARAM_VARGLOBAL`
* `PARAM_ALTVALUE`
* `PARAM_FLAG`
* `PARAM_VARGLOBAL_EXP`
* `PARAM_ALTVALUE_EXP`
* `PARAM_FLAG_EXP`
* `PARAM_EXTENSION`
* `PARAM_8DIRECTIONS`
* `PARAM_MVT`
* `PARAM_STRINGGLOBAL`
* `PARAM_STRINGGLOBAL_EXP`
* `PARAM_PROGRAM2`
* `PARAM_ALTSTRING`
* `PARAM_ALTSTRING_EXP`
* `PARAM_EFFECT`
* `PARAM_CHAR_ENCODING_INPUT`
* `PARAM_CHAR_ENCODING_OUTPUT`
* `67` - Runtime/exporter ID

The following parameter types are valid for expressions:
* `EXPPARAM_LONG` (int32 or float) - a number
* `EXPPARAM_STRING` (pointer to string) - a string

### Custom parameters
For actions and conditions, you can define custom parameter types.
Take your 0-based custom parameter ID and add `PARAM_EXTBASE` to it, then Fusion will call `InitParameter`, `EditParameter`, and `GetParameterString` with that value.
In the action/condition functions, the custom parameters are pointers to `paramExt`.
