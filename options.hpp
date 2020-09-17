
#ifndef SAM_OPTIONS_HPP_INCLUDED
#define SAM_OPTIONS_HPP_INCLUDED
#pragma once

#include "option/behavior.hpp"
#include "option/image_format.hpp"

#include "soil2/soil2.h"

#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"

struct Options {
	option::Behavior	behaviorX;
	option::Behavior	behaviorY;
	unsigned int		channels;
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
		, imageFormat(imageFormat) {

		switch (imageFormat) {
			case option::ImageFormat::a: {
				channels = SOIL_LOAD_L;
				break;
			}
			case option::ImageFormat::l: {
				channels = SOIL_LOAD_L;
				break;
			}
			case option::ImageFormat::la: {
				channels = SOIL_LOAD_LA;
				break;
			}
			case option::ImageFormat::rgb: {
				channels = SOIL_LOAD_RGB;
				break;
			}
			case option::ImageFormat::rgba: {
				channels = SOIL_LOAD_RGB;
				break;
			}
			case option::ImageFormat::srgb: {
				channels = SOIL_LOAD_RGB;
				break;
			}
			case option::ImageFormat::srgba: {
				channels = SOIL_LOAD_RGB;
				break;
			}
		}
	}

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & behaviorX;
		ar & behaviorY;
		ar & channels;
		ar & imageFormat;
	}
};
#endif // INCLUDE_GUARD
