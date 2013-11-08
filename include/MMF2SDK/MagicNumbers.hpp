#ifndef MMF2SDK_MagicNumbers_HeaderPlusPlus
#define MMF2SDK_MagicNumbers_HeaderPlusPlus

#include "SDKResources.h"

//kpxGetInfos
enum
{
	KGI_VERSION,         //Version (required)
	KGI_NOTUSED,         //Not used
	KGI_PLUGIN,          //Version for plug-in (required)
	KGI_MULTIPLESUBTYPE, //Allow sub-types
	KGI_NOTUSED2,        //Reserved
	KGI_ATX_CONTROL,     //Not used
	KGI_PRODUCT,         //Minimum product the extension is compatible with
	KGI_BUILD,           //Minimum build the extension is compatible with
	KGI_UNICODE,         //Returns TRUE if the extension is in Unicode
};

#define EXT_VERSION1 0x200 //C&C, TGF
#define EXT_VERSION2 0x300 //MMF1
#define EXT_VERSION3 0x400 //MMF2

#define EXT_PLUGIN_VERSION1 0x100
#define EXT_PLUGIN_VERSION2 0x200

#define EXT_ATXCTRL_VERSION1 0x100 //Not used

//Values to return for KGI_BUILD
enum
{
	PRODUCT_VERSION_HOME=1,              //TGF or above
	PRODUCT_VERSION_STANDARD,            //MMF Standard or above
	PRODUCT_VERSION_DEV,                 //MMF Developer or above
	PRODUCT_VERSION_DELUXEGOLDCOLLECTOR, //:)
};

//GetFilters
#define GETFILTERS_IMAGES 0x0001
#define GETFILTERS_SOUNDS 0x0002

//Return codes
#define CREATE_OBJECT_OK    0
#define CREATE_OBJECT_ERROR (-1)

#endif
