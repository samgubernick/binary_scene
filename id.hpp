
#ifndef SAM_BINARY_DATA_ID_HPP_INCLUDED
#define SAM_BINARY_DATA_ID_HPP_INCLUDED
#pragma once

#include <string>

// required for uint_8
#include <cstdint>

namespace sam::binary_data {
enum class Id : uint8_t
{
	None,
	Exit,
	Help,
	Info,
	Menu,
	MoreInfo,
	Options,
	Pause,
	Play,
	ThemeEditor,
	Balloons,
	ButtonsLevel,
	Platform,
	Shooter,
	Back,
	AreYouSure,
	Confirm,
	Custom,
	Customize,
	EnterName,
	Example,
	Loading,
	Max,
	Maximum,
	Min,
	Minimum,
	Name,
	No,
	Off,
	On,
	Preview,
	ProfileName,
	Restart,
	Resume,
	ThemeCurrent,
	Value,
	Yes,
	Action,
	Audio,
	AvailableLanguages,
	Bgm,
	Buttons,
	Controls,
	Defaultx,
	Details,
	Disabled,
	DrawInBackground,
	Effects,
	Enabled,
	ForceFeedback,
	Fullscreen,
	Gamepad,
	HapticResponse,
	Keyboard,
	Mouse,
	Music,
	Mute,
	Quality,
	Resolution,
	Sfx,
	Sound,
	Theme,
	Video,
	Volume,
	Window,
	WindowMode,
	Color,
	Black,
	BlackAndWhite,
	Blue,
	Green,
	Grayscale,
	Orange,
	Red,
	White,
	Yellow,
	Language,
	ConfirmLanguage,
	LanguageSelector,
	BackArrow,
	ForwardArrow,
	MinusSign,
	PlusSign,
	Checked,
	Unchecked,
	Background,
	OnBackground,
	OnBackgroundAccent,
	OnPrimary,
	OnPrimaryAccent,
	OnSecondary,
	OnSecondaryAccent,
	OnSurface,
	OnSurfaceAccent,
	Primary,
	PrimaryVariant,
	Secondary,
	SecondaryVariant,
	Surface,
	CurrentColor,
	NewColor,
	SelectColor,
};
}
#endif // INCLUDE_GUARD
