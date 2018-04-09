Lets Fusion know which kinds of filters your extension supports.
```cpp
#ifdef FUSION_GET_FILTERS
auto FUSION_API GetFilters(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t flags, void const *const) noexcept
-> fusion::boolean
```
If `flags` has the bits set for the filters you support, return `FUSION_GET_FILTERS_SUPPORTED`.
Otherwise, return `FUSION_GET_FILTERS_NOT_SUPPORTED`.

## Example
```cpp
#ifdef FUSION_GET_FILTERS
auto FUSION_API GetFilters(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t flags, void const *const) noexcept
-> fusion::boolean
{
	if(flags&GETFILTERS_IMAGES)
	{
		return FUSION_GET_FILTERS_SUPPORTED;
    }
	if(flags&GETFILTERS_SOUNDS)
	{
		return FUSION_GET_FILTERS_SUPPORTED;
	}
	return FUSION_GET_FILTERS_NOT_SUPPORTED;
}
#endif
```
