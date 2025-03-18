
#ifndef SAM_BINARY_DATA_LAYOUT_TAG_HPP_INCLUDED
#define SAM_BINARY_DATA_LAYOUT_TAG_HPP_INCLUDED
#pragma once

// required for uint_8
#include <cstdint>

namespace sam::binary_data {
enum class LayoutTag : int8_t
{
	Any,
	Balloon,
	First,
	Game,
	Level,
	LevelSelect,
	MainMenu,
	MainMenuSub,
	None,
	Options,
	OverlayTop,
	Popup,
	PopupGameControls,
	InGameMenu,
};
}
#endif // INCLUDE_GUARD
