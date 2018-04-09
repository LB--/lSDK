#include "FusionAPI.hpp"

HINSTANCE fusion::DLL = 0;
#ifdef FUSION_NO_DLL_MAIN
BOOL WINAPI DllMain(HINSTANCE dll, DWORD reason, LPVOID reserved) noexcept
{
	if(reason == DLL_PROCESS_ATTACH)
	{
		fusion::DLL = dll;
	}
	return TRUE;
}
#endif
