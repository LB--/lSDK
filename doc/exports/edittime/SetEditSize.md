If you export this function, Fusion assumes your object can be resized and will call this function accordingly.
```cpp
#ifdef FUSION_SET_EDIT_SIZE
auto FUSION_API SetEditSize(mv *const mV, SerializedEditData *serialized_edit_data, std::int32_t const width, std::int32_t const height) noexcept
-> std::int32_t
```
You should store the `width` and `height` values in `serialized_edit_data`.
If you accept the new size, return `FUSION_SET_EDIT_SIZE_CHANGED`.
Otherwise return `FUSION_SET_EDIT_SIZE_NOT_CHANGED`.
