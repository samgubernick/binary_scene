
#ifndef SAM_BINARY_DATA_OPTION_IMAGE_FORMAT_HPP_INCLUDED
#define SAM_BINARY_DATA_OPTION_IMAGE_FORMAT_HPP_INCLUDED
#pragma once

namespace sam
{
	namespace binary_data
	{
		namespace option
		{
			enum class ImageFormat:uint8_t
			{
				a,
				l,
				la,
				rgb,
				rgba,
				srgb,
				srgba,
			};
		}
	}
}
#endif // INCLUDE_GUARD
