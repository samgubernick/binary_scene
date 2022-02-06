
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
			uint16_t version;

			Sprite() : version(0) { }

			Sprite(std::string name)
				: name(name)
				, version(0)
			{ }
		private:
			friend class bitsery::Access;
			template<typename S>
			void serialize(S & s)
			{
				s.value2b(version);
				s.text1b(name, 512);
				s.container(animations, 512);
			}
		};
	}
}
#endif // INCLUDE_GUARD
