This function is part of the Windows API for DLLs, and does not need to be exported.
if you implement it yourself, you need to correctly update the value of `fusion::DLL`.
```cpp
#ifdef FUSION_DLL_MAIN
BOOL WINAPI DllMain(HINSTANCE dll, DWORD reason, LPVOID reserved) noexcept
```
If `reason` is `DLL_PROCESS_ATTACH`, store `dll` into `fusion::DLL`.
