This is a required function that Fusion calls to get information about your extension at both edittime and runtime.
```cpp
#ifdef FUSION_GET_EXTENSION_INFO
auto FUSION_API GetRunObjectInfos(mv *const mV, kpxRunInfos *const run_info) noexcept
-> std::int16_t
```
You must fill in all the data members of `run_info` with appropriate values.

| `kpxRunInfos` member | Value to store |
| --- | --- |
| `identifier` | This must be a value that is unique to your extension and not the same as any other extension. It must never change over the course of your extension's existence. |
| `version` | The current version of the `SerializedEditData` structure, used to inform Fusion when it should call `UpdateEditStructure`. If you do your own version management, simply store `0`. |
| `editDataSize` | The starting size of the `SerializedEditData` structure. You can still ask Fusion to resize it later. |
| `windowProcPriority` | The priority for processing window messages if your extension implements `WindowProc`. |
| `editFlags` | A combination of `OEFLAG_*` flags. The following flags must not change state after the object is instantiated: `OEFLAG_MOVEMENTS`, `OEFLAG_ANIMATIONS`, `OEFLAG_VALUES`, `OEFLAG_BACKGROUND`, `OEFLAG_SPRITES`, `OEFLAG_TEXT`. |
| `editPrefs` | A combination of `OEPREFS_*` flags. This influences which default properties are shown in the properties pane. |
| `numOfActions`<br>`numOfConditions`<br>`numOfExpressions` | The number of actions/conditions/expressions, which may be dynamic. If you don't yet know, you can store `0` and Fusion will ask again later. |
| `actions`<br>`conditions`<br>`expressions` | You must store a `fusion::*ion_func_array` where the size of the array is exactly the same as `numOf*ions` and each value in the array is a function pointer representing the action/condition/expression function. If the number of ACEs is dynamic, you will typically have all function pointers in the array point to the same function and then perform the dispatch within the function itself. If you don't yet know how many ACEs there are, you can store `nullptr` and Fusion will ask again later. You are responsible for managing the memory of the array - it must remain valid until Fusion unloads your extension or until the next call to this function (in which case you can generate a new array). |

If there is an error, return `FUSION_GET_EXTENSION_INFO_FAILURE`.
Otherwise, return `FUSION_GET_EXTENSION_INFO_SUCCESS`.

If you are using dynamic A/C/Es, you must ensure that existing ACE IDs remain immutable and that only new IDs are used over time. This is especially important once you release your extension - updating to a new version shouldn't necessitate deleting all events and recreating them from scratch to use the correct IDs.

For `kpxRunInfos::editFlags`, you should almost always specify `OEFLAG_VALUES` so that users of your extensions can set alterable values on it.
You should also almost always specify `OEFLAG_NEVERKILL` and `OEFLAG_RUNBEFOREFADEIN`.
Keep in mind that any flags you specify may affect the memory layout of the `RunData` structure, see the doc for that for more information.
If the `RunData` structure does not match the flags you specify here, you will get memory corruption problems at runtime.
If you will not be using dnamically chosen flags, you should define `FUSION_OEFLAGS` as a preprocessor definition in your project settings for all build types and use it to store the flags you have set.
