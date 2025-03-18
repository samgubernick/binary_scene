
#ifndef SAM_BINARY_DATA_OPTION_IMAGE_FORMAT_HPP_INCLUDED
#define SAM_BINARY_DATA_OPTION_IMAGE_FORMAT_HPP_INCLUDED
#pragma once

namespace sam::binary_data::option {
enum class ImageFormat : int8_t
{
	Unknown = 0,
	A = 1,
	L = 2,
	La = 3,
	Rg = 4,
	Rga = 5,
	Rgb = 6,
	Rgba = 7,
	Srgb = 8,
	Srgba = 9,
};
}
#endif // INCLUDE_GUARD
