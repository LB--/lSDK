Fusion calls these required functions once for each `RunData` instance, effectively serving as the constructor and destructor pair.

# `CreateRunObject`
Here you should allocate the neseccary memory (e.g. your C++ runtime class).
```cpp
#ifdef FUSION_FINISH_RUNTIME_STRUCTURE_CONSTRUCTION
auto FUSION_API CreateRunObject(RunData *const run_data, SerializedEditData const *const serialized_edit_data, createObjectInfo *const create_object_info) noexcept
-> std::int16_t
```
When this function is called, the structure is already partially initialized - specifically, the required data structures are done being initialized by Fusion, so you can access e.g. `run_data->rHo.hoAdRunHeader->rh4.rh4Mv` to get the `mv` structure pointer.
The rest of the memory content of the `RunData` structure has each byte set to `0`.

You should copy any necesary information from `SerializedEditData`.

If there is any error, return `FUSION_FINISH_RUNTIME_STRUCTURE_CONSTRUCTION_FAILURE`.
Otherwise, return `FUSION_FINISH_RUNTIME_STRUCTURE_CONSTRUCTION_SUCCESS`.

# `DestroyRunObject`
```cpp
#ifdef FUSION_BEGIN_RUNTIME_STRUCTURE_DESTRUCTION
auto FUSION_API DestroyRunObject(RunData *const run_data, std::int32_t const fast) noexcept
-> std::int16_t
```
Deallocate any memory you allocated in `CreateRunObject`.
If there are no errors, return `FUSION_BEGIN_RUNTIME_STRUCTURE_DESTRUCTION_SUCCESS`.
After this function call, Fusion will clean up the rest of the structure and decallocate it.
