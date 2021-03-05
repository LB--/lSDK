This required function informs Fusion on how much memory to allocate for the `RunData` structure.
```cpp
#ifdef FUSION_GET_RUNTIME_STRUCTURE_SIZE
auto FUSION_API GetRunObjectDataSize(RunHeader *const run_header, SerializedEditData const *const serialized_edit_data) noexcept
-> std::uint16_t
```
In 99.9% of cases you will just return `sizeof(RunData);`, even if you are using dynamic OEFLAGS.

## Example
```cpp
#ifdef FUSION_GET_RUNTIME_STRUCTURE_SIZE
auto FUSION_API GetRunObjectDataSize(RunHeader *const run_header, SerializedEditData const *const serialized_edit_data) noexcept
-> std::uint16_t
{
	return sizeof(RunData);
}
#endif
```
