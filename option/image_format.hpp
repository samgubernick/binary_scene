
#ifndef SAM_BINARY_DATA_OPTION_IMAGE_FORMAT_HPP_INCLUDED
#define SAM_BINARY_DATA_OPTION_IMAGE_FORMAT_HPP_INCLUDED
#pragma once

namespace sam::binary_data::option {
enum class ImageFormat:uint8_t
{
	A,
	L,
	La,
	Rga,
	Rgb,
	Rgba,
	Srgb,
	Srgba,
};
}
#endif // INCLUDE_GUARD
