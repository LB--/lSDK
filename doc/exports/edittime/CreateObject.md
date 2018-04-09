Called when the user instantiates a new instance of your extension from scratch (from the Insert Object dialog).
```cpp
#ifdef FUSION_CREATE_OBJECT
auto FUSION_API CreateObject(mv *const mV, LO *const level_object, SerializedEditData *serialized_edit_data) noexcept
-> std::int32_t
```
If necessary, show a setup dialog.
You should take this opportunity to correctly initialize the `SerializedEditData` structure.
If there is any error, return `FUSION_CREATE_OBJECT_FAILURE`.
Otherwise, return `FUSION_CREATE_OBJECT_SUCCESS`.

This function is optional, so if you don't do anything in it, you don't need to export it.
