These functions deal with the current font color of your extension, and are only called if `GetTextCaps` tells Fusion they are implemented.

# `GetTextClr`
```cpp
#ifdef FUSION_GET_TEXT_COLOR
auto FUSION_API GetTextClr(mv *const mV, SerializedEditData *serialized_edit_data) noexcept
-> COLORREF
```

# `SetTextClr`
```cpp
#ifdef FUSION_SET_TEXT_COLOR
void FUSION_API SetTextClr(mv *const mV, SerializedEditData *serialized_edit_data, COLORREF const color) noexcept
```
