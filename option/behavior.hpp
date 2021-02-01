
#ifndef SAM_BINARY_DATA_OPTION_BEHAVIOR_HPP_INCLUDED
#define SAM_BINARY_DATA_OPTION_BEHAVIOR_HPP_INCLUDED
#pragma once

namespace sam
{
	namespace binary_data
	{
		namespace option
		{
			enum class Behavior:uint8_t
			{
				center,
				mirror,
				repeat,
				stretch,
			};
		}
	}
}
#endif // INCLUDE_GUARD
