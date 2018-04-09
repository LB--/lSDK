If you used any custom parameter IDs in `Get*ionInfos`, you must export these functions.

Store serialized data in `paramExt::pextData` and store the size in `paramExt::pextSize`.
The maximum size of the custom parameter data is `PARAM_EXTMAXSIZE`, and that's it.
You don't have access to the `SerializedEditData` in any of these functions, so you can't store extra information there.
The content of `paramExt::pextData` is written to disk as-is, and you'll need to be able to deserialize it in other runtimes, so you can't store any pointers.

# `InitParameter`
Called to initialize a custom parameter.
```cpp
#ifdef FUSION_INITIALIZE_CUSTOM_PARAMETER
void FUSION_API InitParameter(mv *const mV, std::int16_t const custom_id, paramExt *const param_data) noexcept
{
```

# `EditParameter`
Called whenever the user edits (or first edits) the parameter.
```cpp
#ifdef FUSION_EDIT_CUSTOM_PARAMETER
void FUSION_API EditParameter(mv *const mV, std::int16_t const custom_id, paramExt *const param_data) noexcept
{
```
You'll want to show a dialog.
There's no way to fall back to the expression editor like with the other parameter types.

# `GetParameterString`
Called to get the string to replace `%0` etc. with in the event editor.
```cpp
#ifdef FUSION_GET_CUSTOM_PARAMETER_DISPLAY_STRING
void FUSION_API GetParameterString(mv *const mV, std::int16_t const custom_id, paramExt *const param_data, fusion::string_buffer const display_string_buffer, std::int16_t const display_string_buffer_size) noexcept
{
```
