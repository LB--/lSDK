Called as the mouse moves over the object in the frame editor for fine collision checking.

Export: `IsTransparent=IsObjTransparent`
```cpp
#ifdef FUSION_IS_OBJECT_TRANSPARENT
auto FUSION_API IsObjTransparent(mv *const mV, OI *const level_object, SerializedEditData *serialized_edit_data, std::int32_t const x, std::int32_t const y) noexcept
-> fusion::boolean
```
If the given position is transparent, return `FUSION_IS_OBJECT_TRANSPARENT_TRANSPARENT`.
Otherwise return `FUSION_IS_OBJECT_TRANSPARENT_OPAQUE`.

If you don't export this function, Fusion assumes the entire rectangle your object occupies is opaque.
