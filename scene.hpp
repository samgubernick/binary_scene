
#ifndef SAM_BINARY_DATA_SCENE_HPP_INCLUDED
#define SAM_BINARY_DATA_SCENE_HPP_INCLUDED
#pragma once

#include "sound.hpp"
#include "sprite.hpp"
#include "texture.hpp"

#include "bitsery/serializer.h"
#include "bitsery/traits/string.h"
#include "bitsery/traits/vector.h"

#include <string>
#include <vector>

namespace sam
{
	namespace binary_data
	{
		struct Scene
		{
			std::string name;
			std::vector<Texture> textures;
			std::vector<Sprite> sprites;
			std::vector<Sound> bgm;
			std::vector<Sound> sfx;

			Scene() { }

			Scene(std::string name)
				: name(name)
			{ }

		private:
			friend class bitsery::Access;
			template<typename S>
			void serialize(S & s)
			{
				s.text1b(name, 512);
				s.container(bgm, 8192);
				s.container(sfx, 8192);
				s.container(sprites, 8192);
				s.container(textures, 8192);
			}
		};
	}
}
#endif // INCLUDE_GUARD
