
#ifndef SAM_BINARY_DATA_FACE_NAME_HPP_INCLUDED
#define SAM_BINARY_DATA_FACE_NAME_HPP_INCLUDED
#pragma once

// required for uint_8
#include <cstdint>

namespace sam::binary_data {
enum class FaceName : int8_t
{
	None,
	Primary,
	Secondary,
};
}
#endif // INCLUDE_GUARD
