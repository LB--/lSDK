Called when an object instance is deleted.
```cpp
#ifdef FUSION_REMOVE_OBJECT
void FUSION_API RemoveObject(mv *const mV, LO *const level_object, SerializedEditData *serialized_edit_data, std::uint16_t const count) noexcept
```
`count` refers to how many `LO` instances there are for this `SerializedEditData` instance.
