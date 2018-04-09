These functions are the checkbox counterpart to `GetPropValue` and `SetPropValue`.
While you can have checkbox-only properties, don't forget that most property types can have both a value and a checkbox.

# `GetPropCheck`
```cpp
#ifdef FUSION_GET_PROPERTY_CHECKBOX
auto FUSION_API GetPropCheck(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id) noexcept
-> fusion::boolean
```
If the checkbox should display as ticked, return `FUSION_GET_PROPERTY_CHECKBOX_TICKED`.
Otherwise, return `FUSION_GET_PROPERTY_CHECKBOX_UNTICKED`.
There is currently no tri-state support for checkboxes.

# `SetPropCheck`
```cpp
#ifdef FUSION_SET_PROPERTY_CHECKBOX
void FUSION_API SetPropCheck(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id, fusion::boolean const ticked) noexcept
```
If `ticked` is `FUSION_SET_PROPERTY_CHECKBOX_UNTICKED`, the checkbox has been unticked by the user.
Otherwise it was ticked and `ticked` is `FUSION_SET_PROPERTY_CHECKBOX_TICKED`.

You can call `mvRefreshProp` if you decide to ignore the user's action here.
