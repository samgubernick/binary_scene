
#ifndef SAM_ANIMATION_HPP_INCLUDED
#define SAM_ANIMATION_HPP_INCLUDED
#pragma once

#include "end_of_animation.hpp"
#include "texture.hpp"

#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/serialization/vector.hpp"

#include <string>
#include <vector>

struct Animation {
	std::string name;
	std::vector<Texture> textures;
	double speed_default;
	double speed_slow;
	EndOfAnimation endOfAnimation;

	Animation() {

	}

	Animation(std::string name)
		: name(name) {

	}

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & endOfAnimation;
		ar & name;
		ar & textures;
	}
};
#endif // INCLUDE_GUARD
