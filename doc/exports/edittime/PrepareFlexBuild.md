Called when exporting to the Flash runtime.
```cpp
#ifdef FUSION_PREPARE_FLEX_BUILD
void FUSION_API PrepareFlexBuild(mv *const mV, SerializedEditData *serialized_edit_data, fusion::wstring_view const temp_folder) noexcept
```
This function was made for old versions of EDIF that did not include the extension JSON as a resource but instead as a separate file that needed to be copied.
