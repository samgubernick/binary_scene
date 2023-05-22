
#ifndef SAM_BINARY_DATA_LAYOUT_TAG_HPP_INCLUDED
#define SAM_BINARY_DATA_LAYOUT_TAG_HPP_INCLUDED
#pragma once

// required for uint_8
#include <cstdint>

namespace sam { namespace binary_data
{
enum class LayoutTag : uint8_t
{
	any,
	balloon,
	first,
	game,
	level,
	levelSelect,
	mainMenu,
	mainMenuSub,
	none,
	options,
	overlayTop,
	popup,
	popupGameControls,
	inGameMenu,
};
}}
#endif // INCLUDE_GUARD
