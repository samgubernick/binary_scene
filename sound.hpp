
#ifndef SAM_BINARY_DATA_SOUND_HPP_INCLUDED
#define SAM_BINARY_DATA_SOUND_HPP_INCLUDED
#pragma once

#include "bitsery/serializer.h"
#include "bitsery/traits/string.h"

#include <string>

namespace sam
{
	namespace binary_data
	{
		struct Sound
		{
			enum class Group:uint8_t
			{
				bgm,
				custom,
				sfx,
				none,
			};

			std::string	name;
			std::string	path;
			std::string	hash;
			uint32_t	id;
			Group		group;

			Sound()
				: group(Group::none)
				, id(0)
			{ }

			Sound(std::string	name,
				  std::string	path,
				  Group			group)
				: name(name)
				, path(path)
				, id(0)
				, group(group)
			{
				hash = path;
			}
		private:
			friend class bitsery::Access;
			template<typename S>
			void serialize(S & s)
			{
				s.text1b(name, 512);
				s.text1b(path, 1024);
				s.text1b(hash, 1024);
				s.value4b(id);
				s.value1b(group);
			}
		};
	}
}
#endif // INCLUDE_GUARD
