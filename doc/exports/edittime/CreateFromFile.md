Called after `UsesFile` if the user decided to pick your extension.
```cpp
#ifdef FUSION_CREATE_FROM_FILE
void FUSION_API CreateFromFile(mv *const mV, fusion::string_view const file_path, SerializedEditData *serialized_edit_data) noexcept
```
There is no way to cancel creating the object in this function like there is for `CreateObject` - if there is any error, report it to the user and then try to act as if `CreateObject` had been called instead.
