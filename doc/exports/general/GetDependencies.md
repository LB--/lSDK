This optional function lets Fusion know which external files to include in the built project, e.g. dynamic link libraries.
```cpp
#ifdef FUSION_GET_DEPENDENCIES
auto FUSION_API GetDependencies() noexcept
-> fusion::string_array_view
```
Each element of the array should be a relative filename to the depended-upon file.
Paths are relative to the root of Fusion's install directory.
The array you return must be valid until your extension is unloaded or until the next call to this function.
If you don't have any dependencies, you can return `nullptr` or just don't export this function.
