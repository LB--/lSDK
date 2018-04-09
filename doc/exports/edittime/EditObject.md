Called when the user double-clicks on the object or chooses Edit from the right-click menu.
```cpp
#ifdef FUSION_EDIT_OBJECT
auto FUSION_API EditObject(mv *const mV, OI *const object_info, LO *const level_object, SerializedEditData *serialized_edit_data) noexcept
-> std::int32_t
```
You can show the same setup dialog from `CreateObject`, or do nothing.
If you made changes to the editdata structure, return `FUSION_EDIT_OBJECT_CHANGES_MADE`.
Otherwise, return `FUSION_EDIT_OBJECT_NO_CHANGES`.
