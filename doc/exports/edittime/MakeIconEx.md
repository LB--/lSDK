Called just after creating the object to get the icon to use in the object list and event editor.
```cpp
#ifdef FUSION_MAKE_ICON
auto FUSION_API MakeIconEx(mv *const mV, cSurface *const icon, fusion::string_buffer const name, OI *const object_info, SerializedEditData *serialized_edit_data) noexcept
-> std::int32_t
```
If there is any error, return `FUSION_MAKE_ICON_FAILURE`.
Otherwise return `FUSION_MAKE_ICON_SUCCESS`.

You can store a custom name into `name`, but the size of the buffer is not known.
In testing it appears to be up to 79 characters including the null terminator, but until we have official word on this, you should avoid touching it.

If you don't export this function, Fusion will load the `EXO_ICON` bitmap resource from your resource file.

## Example
```cpp
#ifdef FUSION_MAKE_ICON
auto FUSION_API MakeIconEx(mv *const, cSurface *const icon, fusion::string_buffer const, OI *const, SerializedEditData *) noexcept
-> std::int32_t
{
	if(icon && icon->LoadImage(fusion::DLL, EXO_ICON))
	{
		return FUSION_MAKE_ICON_SUCCESS;
	}
	return FUSION_MAKE_ICON_FAILURE;
}
#endif
```
