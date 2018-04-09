Every time the user opens the properties pane for your extension inside Fusion, `GetProprties` is called to get the initial set of properties.
As the user interacts with the properties you may add and remove properties as needed in the other functions.

`master_item` is `TRUE` if these functions are called for the primary object of a multiple selection, e.g. the user selected multiple objects with different `SerializedEditData`s.
It is also `TRUE` if this is the only object in the selection.

# `GetProperties`
```cpp
#ifdef FUSION_GET_PROPERTIES
auto FUSION_API GetProperties(mv *const mV, SerializedEditData *serialized_edit_data, fusion::boolean const master_item) noexcept
-> fusion::boolean
```
For most simple extensions you will just have a static `PropData` array made with the `PropData_*` macros and ended with `PropData_End()`.
You can pass such arrays to `mvInsertProps` - typically you will want to populate `PROPID_TAB_GENERAL`, but you can use the others as well.
In older versions of Fusion 2.x there were multiple custom property tabs, but currently there is only `PROPID_TAB_CUSTOM1` which has a calendar icon.

The first parameter of each `PropData_*` macro is the ID of the property - this value must be greater than or equal to `PROPID_EXTITEM_CUSTOM_FIRST`.
You can use a C-style `enum` inside a `namespace` to help keep track of the IDs if you are using a static property array.

The string parameters of the `PropData_*` macros can be resource identifiers to strings in your resource file, or you can use a string literal such as `(UINT_PTR)TSL("My string")` to provide the strings in line, or you can use a pointer to a dynamically allocated string.

If you are using static property arrays, you are allowed to leave the create param to some properties null and Fusion will call `GetPropCreateParam` and `ReleasePropCreateParam` to dynamically get the value for those properties.
If you are dynamically generating the properties, you should save yourself the trouble and provide values for everything.

For more information about the `PropData_*` macros, refer to the original MMF2 SDK help file.

If there are any errors, return `FUSION_GET_PROPERTIES_FAILURE`.
Otherwise return `FUSION_GET_PROPERTIES_SUCCESS`.

## Example
```cpp
#ifndef FUSION_RUNTIME_ONLY
namespace Prop
{
	enum PropId
	{
		MyProperty1 = PROPID_EXTITEM_CUSTOM_FIRST,
		MyProperty2,
	};
	static PropData general_props[] =
	{
		PropData_CheckBox(Prop::MyProperty1,
			(UINT_PTR)TSL("My property 1"),
			(UINT_PTR)TSL("Just a checkbox")
		),
		PropData_EditMultiLine(Prop::MyProperty2,
			(UINT_PTR)TSL("My proprty 2"),
			(UINT_PTR)TSL("Newlines are in CRLF format")
		),
		PropData_End()
	};
}
#endif

#ifdef FUSION_GET_PROPERTIES
auto FUSION_API GetProperties(mv *const mV, SerializedEditData *serialized_edit_data, fusion::boolean const master_item) noexcept
-> fusion::boolean
{
	mvInsertProps(mV, serialized_edit_data, Prop::general_props, PROPID_TAB_GENERAL, TRUE);
	return FUSION_GET_PROPERTIES_SUCCESS;
}
#endif
```

# `ReleaseProperties`
```cpp
#ifdef FUSION_FREE_PROPERTIES
void FUSION_API ReleaseProperties(mv *const mV, SerializedEditData *serialized_edit_data, fusion::boolean const master_item) noexcept
```
If you needed to dynamically generate properties in `GetProperties`, you can free any memory from that here.
Otherwise this will usually just be a no-op.
