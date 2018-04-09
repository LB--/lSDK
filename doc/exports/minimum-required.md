Most `FUSION_API` functions are optional - Fusion will use default behavior if they are not provided.

The following functions are the minimum required for any build type:
* `GetInfos` - without this, Fusion will not load the extension
* `CreateRunObject` - without this, Fusion will never create the object at runtime
* `DestroyRunObject` - technically you can go without this, but you really shouldn't
* `HandleRunObject` - without this, the runtime will crash immediately by trying to invoke a null function pointer
* `PauseRunObject` - without this, the runtime will crash when pausing the application by trying to invoke a null function pointer
* `ContinueRunObject` - without this, the runtime will crash when unpausing the application by trying to invoke a null function pointer
* `GetRunObjectInfos` - without this, the runtime will exit before ever starting up
* `GetRunObjectDataSize` - it is currently unknown what really happens without this, but it likely will result in corruption at runtime as Fusion doesn't know much memory to allocate for the `RunData` structure

All other functions are optional if you do not need to customize their behavior, though some should be exported together.
If you just need to get started and don't care about a working runtime yet, the only function required for Fusion to load your extension is `GetInfos` - just make sure you also define `KPX_NAME`, `EXO_ICON`, and `EXO_IMAGE` in the resource file.
