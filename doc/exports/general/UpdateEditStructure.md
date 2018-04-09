This function is called at edittime and runtime when Fusion detects that the serialized editdata has an older version than what you reported in `GetRunObjectInfos`.
```cpp
#ifdef FUSION_UPDATE_SERIALIZED_EDITDATA
auto FUSION_API UpdateEditStructure(mv *const mV, void const *const old_serialized_edit_data) noexcept
-> HGLOBAL
```
If you didn't need to make any changes, return `FUSION_UPDATE_SERIALIZED_EDITDATA_NO_CHANGES`.
Otherwise you should return a valid `HGLOBAL` to Fusion containing the new `SerializedEditData` with the `eHeader` copied, but update the `extVersion` member to the current value.
You will want to use the Windows API functions `GlobalAlloc` and `GlobalUnlock`.
Specifically, you must call `GlobalUnlock` before returning to Fusion.
