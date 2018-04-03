#include "FusionAPI.hpp"
#include "RunData.hpp"

#ifdef FUSION_GET_RUNTIME_STRUCTURE_SIZE
auto FUSION_API GetRunObjectDataSize(RunHeader *const run_header, SerializedEditData const *const serialized_edit_data) noexcept
-> std::uint16_t
{
	return sizeof(RunData);
}
#endif

#ifdef FUSION_FINISH_RUNTIME_STRUCTURE_CONSTRUCTION
auto FUSION_API CreateRunObject(RunData *const run_data, SerializedEditData const *const serialized_edit_data, createObjectInfo *const create_object_info) noexcept
-> std::int16_t
{
	return FUSION_FINISH_RUNTIME_STRUCTURE_CONSTRUCTION_SUCCESS;
}
#endif
#ifdef FUSION_BEGIN_RUNTIME_STRUCTURE_DESTRUCTION
auto FUSION_API DestroyRunObject(RunData *const run_data, std::int32_t const fast) noexcept
-> std::int16_t
{
	return FUSION_BEGIN_RUNTIME_STRUCTURE_DESTRUCTION_SUCCESS;
}
#endif

#ifdef FUSION_SERIALIZE_RUNTIME
auto FUSION_API SaveRunObject(RunData *const run_data, HANDLE const file_handle) noexcept
-> fusion::boolean
{
	return FUSION_SERIALIZE_RUNTIME_SUCCESS;
}
#endif
#ifdef FUSION_DESERIALIZE_RUNTIME
auto FUSION_API LoadRunObject(RunData *const run_data, HANDLE const file_handle) noexcept
-> fusion::boolean
{
	return FUSION_DESERIALIZE_RUNTIME_SUCCESS;
}
#endif
