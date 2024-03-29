
#ifndef SAM_BINARY_DATA_ID_HPP_INCLUDED
#define SAM_BINARY_DATA_ID_HPP_INCLUDED
#pragma once

#include <string>

// required for uint_8
#include <cstdint>

namespace sam { namespace binary_data {
enum class Id : uint8_t
{
	none,
	exit,
	help,
	info,
	menu,
	moreInfo,
	options,
	pause,
	play,
	themeEditor,
	balloons,
	buttonsLevel,
	platform,
	shooter,
	back,
	areYouSure,
	confirm,
	custom,
	customize,
	enterName,
	example,
	loading,
	max,
	maximum,
	min,
	minimum,
	name,
	no,
	off,
	on,
	preview,
	profileName,
	restart,
	resume,
	themeCurrent,
	value,
	yes,
	action,
	audio,
	availableLanguages,
	bgm,
	buttons,
	controls,
	defaultx,
	details,
	disabled,
	drawInBackground,
	effects,
	enabled,
	forceFeedback,
	fullscreen,
	gamepad,
	hapticResponse,
	keyboard,
	mouse,
	music,
	mute,
	quality,
	resolution,
	sfx,
	sound,
	theme,
	video,
	volume,
	window,
	windowMode,
	color,
	black,
	blackAndWhite,
	blue,
	green,
	grayscale,
	orange,
	red,
	white,
	yellow,
	language,
	confirmLanguage,
	languageSelector,
	backArrow,
	forwardArrow,
	minusSign,
	plusSign,
	checked,
	unchecked,
	background,
	onBackground,
	onBackgroundAccent,
	onPrimary,
	onPrimaryAccent,
	onSecondary,
	onSecondaryAccent,
	onSurface,
	onSurfaceAccent,
	primary,
	primaryVariant,
	secondary,
	secondaryVariant,
	surface,
	currentColor,
	newColor,
	selectColor,
};
}}
#endif // INCLUDE_GUARD
