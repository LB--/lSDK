This function is called when the user tries to create an object from a file.
```cpp
#ifdef FUSION_USES_FILE
auto FUSION_API UsesFile(mv *const mV, fusion::string_view const file_path) noexcept
-> fusion::boolean
```
If you can correctly call `CreateFromFile` with the given file, return `FUSION_USES_FILE_YES`.
Otherwise, return `FUSION_USES_FILE_NO`.

It is not possible to cancel creating the object in `CreateFromFile`, so be sure to perform full validation here. Unfortunately there's nothing you can do to protect against the possibility of the file changing after you return `FUSION_USES_FILE_YES` but before Fusion calls `CreateFromFile`.
