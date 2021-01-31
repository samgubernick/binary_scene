
#ifndef SAM_BINARY_TEXTURE_HPP_INCLUDED
#define SAM_BINARY_TEXTURE_HPP_INCLUDED
#pragma once

#include "options.hpp"

#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"

#include <string>

namespace sam
{
	namespace binary
	{
		struct Texture
		{
			std::string	name;
			std::string	path;
			Options		options;
			std::string	hash;
			size_t		id;

			Texture()
				: id(0)
			{ }

			Texture(std::string	name,
					std::string	path,
					Options		options)
				: name(name)
				, path(path)
				, options(std::move(options))
				, id(0)
			{
				hash = path;
				hash.append(std::to_string(static_cast<int>(options.imageFormat)))
					.append(std::to_string(static_cast<int>(options.behaviorX)))
					.append(std::to_string(static_cast<int>(options.behaviorY)));
			}

		private:
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive & ar, unsigned int version)
			{
				ar & name;
				ar & path;
				ar & options;
				ar & hash;
				ar & id;
			}
		};
	}
}
#endif // INCLUDE_GUARD
