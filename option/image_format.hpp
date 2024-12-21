
#ifndef SAM_BINARY_DATA_OPTION_IMAGE_FORMAT_HPP_INCLUDED
#define SAM_BINARY_DATA_OPTION_IMAGE_FORMAT_HPP_INCLUDED
#pragma once

namespace sam::binary_data::option {
enum class ImageFormat:uint8_t
{
	Unknown = 0,
	A = 1,
	L = 2,
	La = 3,
	Rga = 4,
	Rgb = 5,
	Rgba = 6,
	Srgb = 7,
	Srgba = 8,
};
}
#endif // INCLUDE_GUARD
