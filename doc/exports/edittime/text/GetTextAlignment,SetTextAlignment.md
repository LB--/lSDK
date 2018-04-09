These functions deal with the current font alignment of your extension, and are only called if `GetTextCaps` tells Fusion they are implemented.

Use any of the flags you told Fusion you supported in `GetTextCaps`:
* `TEXT_ALIGN_LEFT`
* `TEXT_ALIGN_HCENTER`
* `TEXT_ALIGN_RIGHT`
* `TEXT_ALIGN_TOP`
* `TEXT_ALIGN_VCENTER`
* `TEXT_ALIGN_BOTTOM`

# `GetTextAlignment`
```cpp
#ifdef FUSION_GET_TEXT_ALIGNMENT
auto FUSION_API GetTextAlignment(mv *const mV, SerializedEditData *serialized_edit_data) noexcept
-> std::uint32_t
```

# `SetTextAlignment`
```cpp
#ifdef FUSION_SET_TEXT_ALIGNMENT
void FUSION_API SetTextAlignment(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const flags) noexcept
```
