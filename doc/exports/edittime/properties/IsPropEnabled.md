Called to know whether the user is allowed to edit a property.

```cpp
#ifdef FUSION_IS_PROPERTY_ENABLED
auto FUSION_API IsPropEnabled(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id) noexcept
-> fusion::boolean
```
If the property is should not be editable by the user (or if it's not editable anyway but you just want it to look greyed out instead of black) return `FUSION_IS_PROPERTY_ENABLED_DISABLED`.
Otherwise return `FUSION_IS_PROPERTY_ENABLED_ENABLED`.
