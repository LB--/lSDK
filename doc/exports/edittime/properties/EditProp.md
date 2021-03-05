This function is called when the user presses a button on properties with a clickable button.
```cpp
#ifdef FUSION_PROPERTY_BUTTON_PRESSED
auto FUSION_API EditProp(mv *const mV, SerializedEditData *serialized_edit_data, std::uint32_t const property_id) noexcept
-> fusion::boolean
```
If changes are made, return `FUSION_PROPERTY_BUTTON_PRESSED_SAVE_CHANGES` and Fusion will call `GetPropValue` for the master item of the selection and then `SetPropValue` for the other items in the selection if there are multiple selected objects, so that the new value is syncronized across the entire selection.
Otherwise, return `FUSION_PROPERTY_BUTTON_PRESSED_CANCEL_CHANGES`.
Returning `FUSION_PROPERTY_BUTTON_PRESSED_CANCEL_CHANGES` will also cause Fusion to ignore any changes you made to the editdata.
