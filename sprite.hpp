
#ifndef SAM_BINARY_DATA_SPRITE_HPP_INCLUDED
#define SAM_BINARY_DATA_SPRITE_HPP_INCLUDED
#pragma once

#include "animation.hpp"

#include "bitsery/serializer.h"
#include "bitsery/traits/string.h"
#include "bitsery/traits/vector.h"

#include <string>
#include <vector>

namespace sam
{
	namespace binary_data
	{
		struct Sprite
		{
			std::string name;
			std::vector<Animation> animations;

			Sprite() { }

			Sprite(std::string name)
				: name(name)
			{ }
		private:
			friend class bitsery::Access;
			template<typename S>
			void serialize(S & s)
			{
				s.text1b(name, 512);
				s.container(animations, 512);
			}
		};
	}
}
#endif // INCLUDE_GUARD
