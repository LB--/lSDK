The `SerializedEditData` structure is one that you must define yourself, but which Fusion ultimately controls and owns.
The entire memory content of the structure is stored on disk inside the MFA or executable, so it can't contain any pointers or types with constructors/destructors.
You can only have plain data members in this structure.
The destructor and all constructors and assignment coperators must be explicitly deleted. The first data member must be the `extHeader` structure.

You can use `static_assert(fusion::is_valid_editdata_structure());` after the structure definition to be sure that you have correctly adhered to the rules.

The editdata structure can also be resized dynamically if you ask Fusion with `mvReAllocEditData` - see the example below.
Since you will likely be storing strings and other dynamically-sized content in this structure, you should really only store two other data members: the size of the serialized data, and the array of serialized data.
Treat it as an in-memory file that you serialize to and deserialize from as needed.

Be aware that any file paths you store must always occupy at least `_MAX_PATH` characters in the structure, as `UpdateFileNames` must be able to modify the file paths without resizing the structure.

Throughout the Fusion API functions, there are three ways the editdata structure can be passed:
* `SerializedEditData *serialized_edit_data` - you can modify the content of the structure and ask for it to be resized with `mvReAllocEditData`
* `SerializedEditData *const serialized_edit_data` - you can modify the content of the structure, but calls to `mvReAllocEditData` will fail, so it can't be resized
* `SerializedEditData const *const serialized_edit_data` - the structure is completely immutable - you can't change the content or resize it

In multiple cases, the same function is allowed to resize the structure at edittime but not at runtime, be sure to pay close attention to the documentation for those cases.

## Example definition
```cpp
struct SerializedEditData final
{
	extHeader eHeader; //must be first data member

	SerializedEditData() = delete;
	SerializedEditData(SerializedEditData const &) = delete;
	SerializedEditData(SerializedEditData &&) = delete;
	SerializedEditData &operator=(SerializedEditData &&) = delete;
	SerializedEditData &operator=(SerializedEditData const &) = delete;
	~SerializedEditData() = delete;

	auto begin() noexcept
	{
		return reinterpret_cast<char *>(&serialized_data);
	}
	auto end() noexcept
	{
		return reinterpret_cast<char *>(&serialized_data)+serialized_size;
	}
	auto begin() const noexcept
	{
		return reinterpret_cast<char const *>(&serialized_data);
	}
	auto end() const noexcept
	{
		return reinterpret_cast<char const *>(&serialized_data)+serialized_size;
	}

#ifndef FUSION_RUNTIME_ONLY
	static void set_serialized_data(mv *mV, SerializedEditData *&serialized_edit_data, std::string const &data)
	{
		if(SerializedEditData *t = (SerializedEditData *)mvReAllocEditData(mV, serialized_edit_data, sizeof(SerializedEditData)+data.size()))
		{
			serialized_edit_data = t;
		}
		else
		{
			throw std::runtime_error{"Could not resize edit data to fit all data ("+std::to_string(data.size())+" bytes)"};
		}
		serialized_edit_data->serialized_size = data.size();
		std::memcpy(serialized_edit_data->begin(), data.data(), data.size());
	}
#endif

	std::uint32_t serialized_size;
	char serialized_data[1]; //must be last data member
};

static_assert(fusion::is_valid_editdata_structure());
```
