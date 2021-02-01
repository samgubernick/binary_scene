
#ifndef SAM_BINARY_DATA_END_OF_ANIMATION_HPP_INCLUDED
#define SAM_BINARY_DATA_END_OF_ANIMATION_HPP_INCLUDED
#pragma once

namespace sam
{
	namespace binary_data
	{
		enum class EndOfAnimation:uint8_t
		{
			reset,
			reverse,
			stop,
		};
	}
}
#endif // INCLUDE_GUARD
