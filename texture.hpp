
#ifndef SAM_BINARY_DATA_TEXTURE_HPP_INCLUDED
#define SAM_BINARY_DATA_TEXTURE_HPP_INCLUDED
#pragma once

#include "options.hpp"

#include "bitsery/serializer.h"
#include "bitsery/traits/string.h"

#include <string>

namespace sam
{
	namespace binary_data
	{
		struct Texture
		{
			std::string	name;
			std::string	path;
			Options		options;
			std::string	hash;
			uint32_t	id;
			uint16_t	version;

			Texture()
				: id(0)
				, version(0)
			{ }

			Texture(std::string	name,
					std::string	path,
					Options		options)
				: name(name)
				, path(path)
				, options(std::move(options))
				, id(0)
				, version(0)
			{
				hash = path;
				hash.append(std::to_string(static_cast<int>(options.imageFormat)))
					.append(std::to_string(static_cast<int>(options.behaviorX)))
					.append(std::to_string(static_cast<int>(options.behaviorY)));
			}
		private:
			friend class bitsery::Access;
			template<typename S>
			void serialize(S & s)
			{
				s.value2b(version);
				s.text1b(name, 512);
				s.text1b(path, 1024);
				s.object(options);
				s.text1b(hash, 512);
				s.value4b(id);
			}
		};
	}
}
#endif // INCLUDE_GUARD
