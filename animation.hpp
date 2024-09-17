
#ifndef SAM_BINARY_DATA_ANIMATION_HPP_INCLUDED
#define SAM_BINARY_DATA_ANIMATION_HPP_INCLUDED
#pragma once

#include "end_of_animation.hpp"
#include "texture.hpp"

#include "bitsery/serializer.h"
#include "bitsery/traits/vector.h"

#include <string>
#include <vector>

namespace sam::binary_data {
struct Animation
{
	Animation()
		: endOfAnimation{EndOfAnimation::Stop}
		, name{""}
		, speedDefault{0.0}
		, speedSlow{0.0}
		, version{0}
	{ }

	Animation(std::string name)
		: name{name}
		, speedDefault{0.0}
		, speedSlow{0.0}
		, endOfAnimation{EndOfAnimation::Stop}
		, version{0}
	{ }
public:
	std::string name;
	std::vector<Texture> textures;
	double speedDefault;
	double speedSlow;
	EndOfAnimation endOfAnimation;
	uint16_t version;
private:
	friend class bitsery::Access;
	template<typename S>
	void serialize(S & s)
	{
		s.value2b(version);
		s.value1b(endOfAnimation);
		s.text1b(name, 512);
		s.value8b(speedDefault);
		s.value8b(speedSlow);
		s.container(textures, 64);
	}
};
}
#endif // INCLUDE_GUARD
