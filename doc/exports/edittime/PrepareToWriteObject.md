Called when a `SerializedEditData` instance is being wriiten to disk (MFA, executable, other exporter, etc).
```cpp
 FUSION_PREPARE_TO_SAVE
void FUSION_API PrepareToWriteObject(mv *const mV, SerializedEditData *const serialized_edit_data, OI *const object_info) noexcept
```
The given `serialized_edit_data` is a temporary copy that can't be resized, any changes are only written to disk and don't affect the current original instance.

If you find yourself needing to use this function, you are doing something very wrong.
