These functions are how your extension and Fusion communicate about the editable values of the properties.
You will typically store your own version of the values serialized in `SerializedEditData` and convert to and from the correct type of `CPropValue`.

If a proprty has a checkbox for any reason, you will need to also implement `GetPropCheck` and `SetPropCheck` separately.

# `GetPropValue`
```cpp
#ifdef FUSION_GET_PROPERTY_VALUE
auto FUSION_API GetPropValue(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id) noexcept
-> CPropValue *
```
For most properties that have a text value, you will want to return `new CPropStringValue`.
See the original MMF2 SDK help file for specifics on other property types.
Fusion will `delete` the returned values on its own.

# `SetPropValue`
```cpp
#ifdef FUSION_SET_PROPERTY_VALUE
void FUSION_API SetPropValue(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id, CPropValue *const property_value) noexcept
```
In normal C++ code you would use `dynamic_cast`, but here you should use `reinterpret_cast` to get the desired `property_value` type because Fusion may use a different run time type information implementation than your compiler. Additonally, older versions of Fusion might give `CPropDataValue` instead of `CPropStringValue` - these structures are designed to be memory-compatible with each other, but obviously a `dynamic_cast` would fail in this case.

If you don't accept the new value or you accept it but modify it, you can call `mvRefreshProp` to have Fusion call `GetPropValue` and display the new value.
