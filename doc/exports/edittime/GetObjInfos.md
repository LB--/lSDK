Fusion calls this when enumerating installed extensions and also when generating the properties pane.
```cpp
#ifdef FUSION_GET_EXTENSION_METADATA
void FUSION_API GetObjInfos(mv *const mV, SerializedEditData *serialized_edit_data,
	fusion::string_buffer const extension_name_buffer/*255*/,
	fusion::string_buffer const extension_author_buffer/*255*/,
	fusion::string_buffer const extension_copyright_buffer/*255*/,
	fusion::string_buffer const extension_description_buffer/*1024*/,
	fusion::string_buffer const extension_website_buffer/*255*/
) noexcept
```
You must fill each buffer with the relevant information.
The buffer sizes are indicated by the C-style comments after each parameter name.
If `serialized_edit_data` is not `nullptr`, you can vary the content of the buffers for the properties pane.

This function is technically optional - if you don't export it, Fusion will instead load the object name from the `KPX_NAME` resource defined in your resource file. For example:
```rc
STRINGTABLE 
BEGIN
	KPX_NAME "My Extension"
END
```
The other fields will be blank.
