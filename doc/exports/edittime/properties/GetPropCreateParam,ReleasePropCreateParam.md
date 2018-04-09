If you are using static property arrays for `GetProprties`, some property types allow passing null for their create param.
In that case, Fusion will call these functions to dynamically get the create params.
However, if you are dynamically generating the property arrays, you shouldn't need or want to use these functions.

# `GetPropCreateParam`
```cpp
#ifdef FUSION_GET_PROPERTY_PARAM
auto FUSION_API GetPropCreateParam(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id) noexcept
-> std::int32_t
```
You may have to `reinterpret_cast` a pointer into the `std::int32_t` return type.
Don't return null unless the property type has default behavior.

# `ReleasePropCreateParam`
```cpp
#ifdef FUSION_FREE_PROPERTY_PARAM
void FUSION_API ReleasePropCreateParam(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id, std::int32_t const param) noexcept
```
You may have to `reinterpret_cast` the `std::int32_t` back into the original pointer type before freeing the memory.
