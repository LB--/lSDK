These optional functions are called for each `SerializedEditData` between calls to `Initialize` and `Free`.
At edittime, you can modify and resize the editdata.
At runtime, the editdata is immutable and cannot be resized.
If possible, avoid using these functions.
They are both optional and may be omitted from your exports file.

# `LoadObject`
```cpp
#ifdef FUSION_LOAD_OBJECT
auto FUSION_API LoadObject(mv *const mV, fusion::string_view const filename, SerializedEditData *serialized_edit_data, std::int32_t const reserved) noexcept
-> std::int32_t
```
`filename` is the filename of the current application.
If there is any error, return `FUSION_LOAD_OBJECT_FAILURE`.
Otherwise, return `FUSION_LOAD_OBJECT_SUCCESS`.

# `UnloadObject`
```cpp
#ifdef FUSION_UNLOAD_OBJECT
void FUSION_API UnloadObject(mv *const mV, SerializedEditData *serialized_edit_data, std::int32_t const reserved) noexcept
```
