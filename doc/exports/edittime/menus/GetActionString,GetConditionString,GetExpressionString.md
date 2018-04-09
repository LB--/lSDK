These functions are called to get the display string to be used in the event editor (actions/conditions) or expression editor (expressions).
```cpp
#ifdef FUSION_GET_ACTION_DISPLAY_STRING
void FUSION_API GetActionString(mv *const mV, std::int16_t const action_id, fusion::string_buffer const display_string_buffer, std::int16_t const display_string_buffer_size) noexcept
{
```
```cpp
#ifdef FUSION_GET_CONDITION_DISPLAY_STRING
void FUSION_API GetConditionString(mv *const mV, std::int16_t const condition_id, fusion::string_buffer const display_string_buffer, std::int16_t const display_string_buffer_size) noexcept
{
```
```cpp
#ifdef FUSION_GET_EXPRESSION_EDITOR_STRING
void FUSION_API GetExpressionString(mv *const mV, std::int16_t const expression_id, fusion::string_buffer const editor_string_buffer, std::int16_t const editor_string_buffer_size) noexcept
{
```
For actions and conditions, the name is shown in the event editor. Use `%0`, ..., `%9`, `%a`, ... `%f` to refer to the first 16 parameters. For conditions, use `%o` to include the object icon. Examples: `Start loop %1 for channel %0`, `%o: On loop %1 for channel %0`

For expressions, the name is the function name of the expression and must be unique and not contain any illegal characters (spaces are allowed). The last character must always be `(`. If the expression returns a string, the second-to-last character should be `$`, though this is only a convention. Examples: `get loop index(`, `get name $(`

Keep in mind that `GetExpressionString` is called continuously for all expression IDs as Fusion validates the expression. This is because the user can type it by hand if they know it, or they may copy and paste. The `editor_string_buffer` is also usually very small (less than 40 characters) so you must avoid lenghty names.

You must export these functions if you export their corresponding `Get*ionMenu` functions.
