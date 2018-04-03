#pragma once

#include "FusionAPI.hpp"

struct SerializedEditData final
{
	static constexpr std::int16_t CURRENT_VERSION = 0;
	extHeader eHeader;

	//Remember: all data members are written to disk in the MFA as-is, so don't use pointers
	//You can ask Fusion to resize this data structure, in that case treat everything after eHeader as an in-memory file
	//e.g.:
	//std::size_t data_size;
	//char data[1]; //must be last data member

	SerializedEditData() = delete;
	SerializedEditData(SerializedEditData const &) = delete;
	SerializedEditData(SerializedEditData &&) = delete;
	SerializedEditData &operator=(SerializedEditData &&) = delete;
	SerializedEditData &operator=(SerializedEditData const &) = delete;
	~SerializedEditData() = delete;
};

static_assert(fusion::is_valid_editdata_structure());
