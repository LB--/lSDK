Called when a new object instance is created.
```cpp
#ifdef FUSION_PUT_OBJECT
void FUSION_API PutObject(mv *const mV, LO *const level_object, SerializedEditData *serialized_edit_data, std::uint16_t const count) noexcept
```
`count` refers to how many `LO` instances there are for this `SerializedEditData` instance.
