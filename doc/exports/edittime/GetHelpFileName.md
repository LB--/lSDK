Used by the Help button in the object properties pane.
```cpp
#ifdef FUSION_GET_HELP_FILE
auto FUSION_API GetHelpFileName() noexcept
-> fusion::string_view
```
Return a path relative to the Fusion root install directory, e.g. `Help/My Extension/Help File.chm`.

This function is optional, if you don't export it the Help button in the properties pane will be disabled.
