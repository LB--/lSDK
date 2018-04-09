Deprecated. Use `MakeIconEx` instead.
```cpp
[[deprecated]] auto FUSION_API MakeIcon(mv *const mV, BITMAPINFO *const bitmap_info, fusion::string_buffer const name, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept
-> std::int32_t
```
You can use `cSurface::SaveImage` to store an image into the `bitmap_info`.
You can store a custom name for the object into `name`, but the size of the buffer is not known.
If there is any error, return `-1`.
Otherwise return `0`.
