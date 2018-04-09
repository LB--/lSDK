These functions give Fusion the name of a parameter for the given action/condition/expression ID.
```cpp
#ifdef FUSION_GET_ACTION_PARAM_NAME
void FUSION_API GetActionTitle(mv *const mV, std::int16_t const action_id, std::int16_t const param_id, fusion::string_buffer const param_name_buffer, std::int16_t const param_name_buffer_size) noexcept
{
```
```cpp
#ifdef FUSION_GET_CONDITION_PARAM_NAME
void FUSION_API GetConditionTitle(mv *const mV, std::int16_t const condition_id, std::int16_t const param_id, fusion::string_buffer const param_name_buffer, std::int16_t const param_name_buffer_size) noexcept
{
```
```cpp
#ifdef FUSION_GET_EXPRESSION_PARAM_NAME
void FUSION_API GetExpressionParam(mv *const mV, std::int16_t const expression_id, std::int16_t const param_id, fusion::string_buffer const param_name_buffer, std::int16_t const param_name_buffer_size) noexcept
{
```
Fill the buffer with the name of the parameter.
For actions and conditions, the name is shown in the title bar of the parameter dialog window.
For expressions, the name is shown between `>` and `<` within the expression editor.

You must export these functions if you export their corresponding `Get*ionMenu` functions.
