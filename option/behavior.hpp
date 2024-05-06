
#ifndef SAM_BINARY_DATA_OPTION_BEHAVIOR_HPP_INCLUDED
#define SAM_BINARY_DATA_OPTION_BEHAVIOR_HPP_INCLUDED
#pragma once

namespace sam::binary_data::option {
enum class Behavior : uint8_t
{
	Center,
	Mirror,
	Repeat,
	Stretch,
};
}
#endif // INCLUDE_GUARD
