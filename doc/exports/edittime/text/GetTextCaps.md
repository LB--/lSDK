Called to inform Fusion of what text capabilities your extension supports.
```cpp
#ifdef FUSION_GET_TEXT_CAPABILITIES
auto FUSION_API GetTextCaps(mv *const mV, SerializedEditData *serialized_edit_data) noexcept
-> std::uint32_t
```
Return a combination of the following flags:
* `TEXT_FONT` if you implement `GetTextFont` and `SetTextFont`
* `TEXT_COLOR` if you implement `GetTextClr` and `SetTextClr`
* Any combination of the below if you implement `GetTextAlignement` and `SetTextAlignement`:
* `TEXT_ALIGN_LEFT`
* `TEXT_ALIGN_HCENTER`
* `TEXT_ALIGN_RIGHT`
* `TEXT_ALIGN_TOP`
* `TEXT_ALIGN_VCENTER`
* `TEXT_ALIGN_BOTTOM`
