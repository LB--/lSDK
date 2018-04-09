Called continuously to draw the object into the frame editor.
```cpp
#ifdef FUSION_EDITOR_DISPLAY
void FUSION_API EditorDisplay(mv *const mV, OI *const object_info, LO *const level_object, SerializedEditData *serialized_edit_data, RECT *const bounds) noexcept
```
If there is any error, you can't do anything but step into it with a debugger.

If you don't export this function, Fusion will load the `EXO_IMAGE` bitmap resource from your resource file.

## Example
```cpp
#ifdef FUSION_EDITOR_DISPLAY
void FUSION_API EditorDisplay(mv *const mV, OI *const, LO *const, SerializedEditData *, RECT *const bounds) noexcept
{
	if(!mV || !bounds)
	{
		return;
	}
	cSurface *const frame_window = WinGetSurface(reinterpret_cast<std::int32_t>(mV->mvIdEditWin));
	if(!frame_window)
	{
		return;
	}
	cSurface *prototype = nullptr;
	if(!GetSurfacePrototype(&prototype, 32, ST_MEMORY, SD_DIB))
	{
		return;
	}
	cSurface icon;
	icon.Create(32, 32, prototype);
	if(!icon.LoadImage(fusion::DLL, EXO_IMAGE, LI_REMAP))
	{
		return;
	}
	icon.SetTransparentColor(icon.GetPixelFast(0, 0));
	if(!icon.Blit(*frame_window, bounds->left, bounds->top, BMODE_TRANSP, BOP_COPY))
	{
		return;
	}
}
#endif
```
