#pragma once

#include "FusionAPI.hpp"

struct RunData final
{
	headerObject rHo;
	rVal rv;

	//Remember: all data members are initialized with 0 in each byte in memory, so you can't store complex class types directly since constructors and destructors are never called
	//You should generally only store a single custom data member: a pointer to your real runtime class, where you can use C++ class data members as normal

	RunData() = delete;
	RunData(RunData const &) = delete;
	RunData(RunData &&) = delete;
	RunData &operator=(RunData &&) = delete;
	RunData &operator=(RunData const &) = delete;
	~RunData() = delete;
};

static_assert(fusion::is_valid_rundata_structure<FUSION_OEFLAGS>());
