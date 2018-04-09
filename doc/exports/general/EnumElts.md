This function is called so you can inform Fusion about handles you are holding to Fusion's internal data types (e.g. images and fonts). This way Fusion can prune unused handles.
```cpp
#ifdef FUSION_ENUMERATE_HANDLES
auto FUSION_API EnumElts(mv *const mV, SerializedEditData *serialized_edit_data, ENUMELTPROC enum_func, ENUMELTPROC undo_func, LPARAM lp1, LPARAM lp2) noexcept
-> std::int32_t
```
You should call `enum_func` for each handle you are holding.
If a call to `enum_func` is non-zero, call `undo_func` for all previously processed handles in reverse order, and then return the value that the failing `enum_func` had returned.
If successful, return `FUSION_ENUMERATE_HANDLES_SUCCESS`.
The first parameter of each function is the handle.
The second parameter of each function is one of `IMAGE_TAB` or `FONT_TAB`.
The third and fourth parameters of each function should be `lp1` and `lp2` respectively.

Handles can be acquired via `DibToImage`, `WinCreateFont`, or `mvEditImage`.
