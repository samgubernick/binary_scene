
#ifndef SAM_BINARY_DATA_END_OF_ANIMATION_HPP_INCLUDED
#define SAM_BINARY_DATA_END_OF_ANIMATION_HPP_INCLUDED
#pragma once

namespace sam::binary_data {
enum class EndOfAnimation : uint8_t
{
	Reset,
	Reverse,
	Stop,
};
}
#endif // INCLUDE_GUARD
