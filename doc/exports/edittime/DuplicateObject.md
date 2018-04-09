Called when the "Clone Object" option is used in Fusion.
```cpp
#ifdef FUSION_CLONE_OBJECT
void FUSION_API DuplicateObject(mv *const mV, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept
```
`serialized_edit_data` is a byte-for-byte copy of the original.
