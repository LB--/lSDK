Most `FUSION_API` functions are optional - Fusion will use default behavior if they are not provided.

The following functions are the minimum required for Edittime builds:
* `GetInfos` - without this, Fusion will not load the extension
* `EditorDisplay` - without this, the extension will not have an icon in the frame editor
* `GetObjInfos` - without this, you must provide a name with `KPX_NAME` after `KPX_MARK` in the resource file, otherwise the extension will show without any name in the Insert Object dialog
* `CreateRunObject` - without this, Fusion will never create the object at runtime
* `DestroyRunObject` - technically you can go without this, but you really shouldn't
* `HandleRunObject` - without this, the runtime will crash immediately by trying to invoke a null function pointer
* `PauseRunObject` - without this, the runtime will crash when pausing the application by trying to invoke a null function pointer
* `ContinueRunObject` - without this, the runtime will crash when unpausing the application by trying to invoke a null function pointer
* `GetRunObjectInfos` - without this, the runtime will exit before ever starting up
* `GetRunObjectDataSize` - it is currently unknown what really happens without this, but it likely will result in corruption at runtime as Fusion doesn't know much memory to allocate for the `RunData` structure

The following functions are the minimum required for the Runtime builds:
* `GetInfos` - see above
* `CreateRunObject` - see above
* `DestroyRunObject` - see above
* `HandleRunObject` - see above
* `PauseRunObject` - see above
* `ContinueRunObject` - see above
* `GetRunObjectInfos` - see above
* `GetRunObjectDataSize` - see above

All other functions are optional if you do not need to customize their behavior, though some come in all-or-nothing pairs or sets.
