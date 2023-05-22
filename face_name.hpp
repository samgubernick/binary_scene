
#ifndef SAM_BINARY_DATA_FACE_NAME_HPP_INCLUDED
#define SAM_BINARY_DATA_FACE_NAME_HPP_INCLUDED
#pragma once

// required for uint_8
#include <cstdint>

namespace sam { namespace binary_data
{
enum class FaceName : uint8_t
{
	none,
	primary,
	secondary,
};
}}
#endif // INCLUDE_GUARD
