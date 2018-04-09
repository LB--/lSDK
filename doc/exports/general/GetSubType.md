This function is required for extensions with multiple subtypes.
```cpp
#ifdef FUSION_GET_SUBTYPE
void FUSION_API GetSubType(SerializedEditData const *const serialized_edit_data, fusion::string_buffer const subtype_buffer, std::int32_t const subtype_buffer_size) noexcept
```
The subtype is a null-terminated string up to `subtype_buffer_size-1` characters in length which you must copy into the buffer pointed to by `subtype_buffer`.
Typically, `subtype_buffer_size` is `1024` - you should find other places in your code to report errors when the subtype would be too long.

Since there is no `mv` parameter, you are very limited with what you can do in this function.
You must be able to determine the subtype from the information in `serialized_edit_data` alone.
Do not try to access global data in this function, as there is no way to know what the value of `mv::mvEditApp` is.

The subtype can later be retrieved from `mv::subType`, but take care to verify that it is correct.
Sometimes `mv::subType` will be `nullptr`, sometimes it will be an empty string, and sometimes it will hold the subtype of an entirely different extension.
For this reason you should prefix all your subtypes with an idenfier unique to your extension (e.g. `kpxRunInfos::identifier`).