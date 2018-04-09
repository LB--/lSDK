#include "FusionAPI.hpp"
#include "lSDK.hpp"

//Initially, these two functions are commented out in exports-edittime.def
//Be sure to uncomment them!

#ifdef FUSION_GET_EXTENSION_METADATA
void FUSION_API GetObjInfos(mv *const mV, SerializedEditData *serialized_edit_data,
	fusion::string_buffer const extension_name_buffer/*255*/,
	fusion::string_buffer const extension_author_buffer/*255*/,
	fusion::string_buffer const extension_copyright_buffer/*255*/,
	fusion::string_buffer const extension_description_buffer/*1024*/,
	fusion::string_buffer const extension_website_buffer/*255*/
) noexcept
{
	lSDK::fill_buffer(extension_name_buffer       , 255 , TSL("Example Extension"));
	lSDK::fill_buffer(extension_author_buffer     , 255 , TSL("Nicholas Braden"));
	lSDK::fill_buffer(extension_copyright_buffer  , 255 , TSL("2018 Nicholas Braden"));
	lSDK::fill_buffer(extension_description_buffer, 1024, TSL("An example extension for extension developers."));
	lSDK::fill_buffer(extension_website_buffer    , 255 , TSL("about:blank"));
	if(serialized_edit_data)
	{
		//You can vary the display of the above values based on the edit data structure, the new values will be shown in the object properties
	}
}
#endif

#ifdef FUSION_GET_HELP_FILE
auto FUSION_API GetHelpFileName() noexcept
-> fusion::string_view
{
	return TSL("Help/ExampleObject.chm");
}
#endif
