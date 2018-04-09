Called when Fusion needs to know the width and height of the object.
```cpp
#ifdef FUSION_GET_OBJECT_BOUNDS
void FUSION_API GetObjectRect(mv *const mV, RECT *const rect, LO *const level_object, SerializedEditData *serialized_edit_data) noexcept
```
`rect.left` and `rect.top` are the actual X and Y coordinates of the `LO` instance and should not be modified. Instead, add your object size to them and store the resulting values in `rect.right` and `rect.bottom`.

If this function is not exported, Fusion assumes your object is 32x32.

## Example
```cpp
#ifdef FUSION_GET_OBJECT_BOUNDS
void FUSION_API GetObjectRect(mv *const, RECT *const rect, LO *const, SerializedEditData *) noexcept
{
	if(rect)
	{
		rect->right = rect->left + 32; //w
		rect->bottom = rect->top + 32; //h
	}
}
#endif
```
