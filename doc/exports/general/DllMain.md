This function is part of the Windows API for DLLs, and does not need to be exported.
If you implement it yourself, you need to correctly update the value of `fusion::DLL`.
```cpp
#ifdef FUSION_DLL_MAIN
BOOL WINAPI DllMain(HINSTANCE dll, DWORD reason, LPVOID reserved) noexcept
```
If `reason` is `DLL_PROCESS_ATTACH`, store `dll` into `fusion::DLL`.

If you don't define this function, add `FUSION_NO_DLL_MAIN` to your preprocessor directives for all build configurations and a default version will be provided for you in `FusionAPI.cpp`.
