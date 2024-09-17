
#ifndef SAM_BINARY_DATA_OPTIONS_HPP_INCLUDED
#define SAM_BINARY_DATA_OPTIONS_HPP_INCLUDED
#pragma once

#include "option/behavior.hpp"
#include "option/image_format.hpp"

#include "bitsery/serializer.h"

#include "soil2/soil2.h"

namespace sam::binary_data {
struct Options
{
public:
	Options()
		: behaviorX{option::Behavior::Center}
		, behaviorY{option::Behavior::Center}
		, channels{0}
		, imageFormat{option::ImageFormat::A}
		, version{0}
	{ }

	Options(
		option::Behavior behaviorX,
		option::Behavior behaviorY,
		option::ImageFormat imageFormat
	)
		: behaviorX{behaviorX}
		, behaviorY{behaviorY}
		, channels{0}
		, imageFormat{imageFormat}
		, version{0}
	{
		switch (imageFormat)
		{
			case option::ImageFormat::A: channels = SOIL_LOAD_L;
			break; case option::ImageFormat::L: channels = SOIL_LOAD_L;
			break; case option::ImageFormat::La: channels = SOIL_LOAD_LA;
			break; case option::ImageFormat::Rga: channels = SOIL_LOAD_RGB;
			break; case option::ImageFormat::Rgb: channels = SOIL_LOAD_RGB;
			break; case option::ImageFormat::Rgba: channels = SOIL_LOAD_RGB;
			break; case option::ImageFormat::Srgb: channels = SOIL_LOAD_RGB;
			break; case option::ImageFormat::Srgba: channels = SOIL_LOAD_RGB;
			break;
		}
	}
public:
	option::Behavior behaviorX;
	option::Behavior behaviorY;
	uint8_t channels;
	option::ImageFormat imageFormat;
	uint16_t version;
private:
	friend class bitsery::Access;
	template<typename S>
	void serialize(S & s)
	{
		s.value2b(version);
		s.value1b(behaviorX);
		s.value1b(behaviorY);
		s.value1b(channels);
		s.value1b(imageFormat);
	}
};
}
#endif // INCLUDE_GUARD
