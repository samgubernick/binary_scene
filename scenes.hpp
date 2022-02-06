
#ifndef SAM_BINARY_DATA_SCENES_HPP_INCLUDED
#define SAM_BINARY_DATA_SCENES_HPP_INCLUDED
#pragma once

#include "scene.hpp"

#include "bitsery/serializer.h"
#include "bitsery/traits/vector.h"

#include <vector>

namespace sam
{
	namespace binary_data
	{
		struct Scenes
		{
			std::vector<Scene> scenes;
			uint16_t version;
		private:
			friend bitsery::Access;
			template<typename S>
			void serialize(S & s)
			{
				s.value2b(version);
				s.container(scenes, 256);
			}
		};
	}
}
#endif // INCLUDE_GUARD
