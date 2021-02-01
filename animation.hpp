
#ifndef SAM_BINARY_DATA_ANIMATION_HPP_INCLUDED
#define SAM_BINARY_DATA_ANIMATION_HPP_INCLUDED
#pragma once

#include "end_of_animation.hpp"
#include "texture.hpp"

#include "bitsery/serializer.h"
#include "bitsery/traits/vector.h"

#include <string>
#include <vector>

namespace sam
{
	namespace binary_data
	{
		struct Animation
		{
			std::string name;
			std::vector<Texture> textures;
			double speedDefault;
			double speedSlow;
			EndOfAnimation endOfAnimation;

			Animation()
				: endOfAnimation(EndOfAnimation::stop)
				, name("")
				, speedDefault(0.0)
				, speedSlow(0.0)
			{ }

			Animation(std::string name)
				: name(name)
				, speedDefault(0.0)
				, speedSlow(0.0)
				, endOfAnimation(EndOfAnimation::stop)
			{ }

		private:
			friend class bitsery::Access;
			template<typename S>
			void serialize(S & s)
			{
				s.value1b(endOfAnimation);
				s.text1b(name, 512);
				s.value8b(speedDefault);
				s.value8b(speedSlow);
				s.container(textures, 64);
			}
		};
	}
}
#endif // INCLUDE_GUARD
