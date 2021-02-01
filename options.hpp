
#ifndef SAM_BINARY_DATA_OPTIONS_HPP_INCLUDED
#define SAM_BINARY_DATA_OPTIONS_HPP_INCLUDED
#pragma once

#include "option/behavior.hpp"
#include "option/image_format.hpp"

#include "bitsery/serializer.h"

#include "soil2/soil2.h"

namespace sam
{
	namespace binary_data
	{
		struct Options
		{
			option::Behavior	behaviorX;
			option::Behavior	behaviorY;
			uint8_t				channels;
			option::ImageFormat	imageFormat;

			Options()
				: behaviorX(option::Behavior::center)
				, behaviorY(option::Behavior::center)
				, channels(0)
				, imageFormat(option::ImageFormat::a)
			{ }

			Options(option::Behavior		behaviorX,
					option::Behavior		behaviorY,
					option::ImageFormat		imageFormat)
				: behaviorX(behaviorX)
				, behaviorY(behaviorY)
				, channels(0)
				, imageFormat(imageFormat)
			{
				switch (imageFormat)
				{
					case option::ImageFormat::a:
					{
						channels = SOIL_LOAD_L;
						break;
					}
					case option::ImageFormat::l:
					{
						channels = SOIL_LOAD_L;
						break;
					}
					case option::ImageFormat::la:
					{
						channels = SOIL_LOAD_LA;
						break;
					}
					case option::ImageFormat::rgb:
					{
						channels = SOIL_LOAD_RGB;
						break;
					}
					case option::ImageFormat::rgba:
					{
						channels = SOIL_LOAD_RGB;
						break;
					}
					case option::ImageFormat::srgb:
					{
						channels = SOIL_LOAD_RGB;
						break;
					}
					case option::ImageFormat::srgba:
					{
						channels = SOIL_LOAD_RGB;
						break;
					}
				}
			}
		private:
			friend class bitsery::Access;
			template<typename S>
			void serialize(S & s)
			{
				s.value1b(behaviorX);
				s.value1b(behaviorY);
				s.value1b(channels);
				s.value1b(imageFormat);
			}
		};
	}
}
#endif // INCLUDE_GUARD
