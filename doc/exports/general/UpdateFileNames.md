When the MFA or runtime executable is relocated, this function is called to fix file paths.
```cpp
#ifdef FUSION_UPDATE_FILENAMES
void FUSION_API UpdateFileNames(mv *const mV, fusion::string_view const app_name, SerializedEditData *serialized_edit_data,
	void (FUSION_API *update_function)(fusion::string_view const app_name, fusion::string_buffer const file_path_buffer/*_MAX_PATH*/)
) noexcept
```
Call `update_function` for each file path you have stored in the editdata.
You cannot resize the editdata at runtime, so you must ensure that every path in the editdata occupies at least `_MAX_PATH` characters.
