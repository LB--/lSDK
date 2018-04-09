These functions are called once for the main application and again for each sub-application at runtime.
For this reason you should be very careful when allocating and deallocating global data in these functions, as you only have one set of global variables.
If possible, avoid using these functions.
They are both optional and may be omitted from your exports file.

# `Initialize`
Export: `Initialize=InitExt`
```cpp
#ifdef FUSION_INITIALIZE
auto FUSION_API InitExt(mv *const mV, fusion::boolean const quiet) noexcept
-> std::int32_t
```
Called shortly after Fusion has loaded your MFX or a sub-application.
If `quiet` is `TRUE`, don't popup error message windows.
If there is any problem, return `FUSION_INITIALIZE_FAILURE`, otherwise return `FUSION_INITIALIZE_SUCCESS`.

# `Free`
Export: `Free=FreeExt`
```cpp
#ifdef FUSION_FREE
auto FUSION_API FreeExt(mv *const mV) noexcept
-> std::int32_t
```
Called shortly before Fusion will unload your MFX or a sub-application.
Always return `FUSION_FREE_SUCCESS`.
