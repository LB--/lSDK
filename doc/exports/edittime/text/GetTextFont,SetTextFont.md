These functions deal with the current font face of your extension, and are only called if `GetTextCaps` tells Fusion they are implemented.
If there is any error, return `FALSE`.
Otherwise, return `TRUE`.

# `GetTextFont`
```cpp
#ifdef FUSION_GET_TEXT_FONT
auto FUSION_API GetTextFont(mv *const mV, SerializedEditData *serialized_edit_data, LOGFONT *const font, void const *const, std::uint32_t const) noexcept
-> fusion::boolean
```
The last two parameters exist for compatibility reasons only and aren't used by Fusion 2.x.

# `SetTextFont`
```cpp
#ifdef FUSION_SET_TEXT_FONT
auto FUSION_API SetTextFont(mv *const mV, SerializedEditData *serialized_edit_data, LOGFONT const *const font, void const *const) noexcept
-> fusion::boolean
```
The last parameter exists for compatibility reasons only and isn't used by Fusion 2.x.
