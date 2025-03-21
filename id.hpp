
#ifndef SAM_BINARY_DATA_ID_HPP_INCLUDED
#define SAM_BINARY_DATA_ID_HPP_INCLUDED
#pragma once

#include <string>

#include <cstdint>

namespace sam::binary_data {
enum class Id : int16_t
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
	Memory,
	ColorSwipe,
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
	Button,
	Buttons,
	Calibrate,
	CancelChanges,
	Channel,
	ControlIndex,
	ControlLocation,
	Controls,
	CurrentValue,
	Defaultx,
	Details,
	DeviceName,
	Devices,
	Disabled,
	DoesControlHaveLights,
	DoesControlLightUp,
	DrawInBackground,
	Edit,
	EditChannel,
	EditName,
	EditResolution,
	Effects,
	Enabled,
	ForceFeedback,
	Fullscreen,
	Gamepad,
	Gameplay,
	HapticResponse,
	InputDevice,
	Keyboard,
	Knob,
	MaxValue,
	Midi,
	MidiDeviceNotConfigured,
	MidiDevicesNotConfigured,
	MinValue,
	Mouse,
	Music,
	Mute,
	OutputDevice,
	Quality,
	RequestToConfigureDevice,
	RequestToConfigureDevices,
	Reset,
	Resolution,
	SaveChanges,
	Sfx,
	Slider,
	Sound,
	Theme,
	UseDefault,
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
