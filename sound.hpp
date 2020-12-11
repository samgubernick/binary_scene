
#ifndef SAM_BINARY_SOUND_HPP_INCLUDED
#define SAM_BINARY_SOUND_HPP_INCLUDED
#pragma once

#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"

#include <string>

namespace sam
{
	namespace binary
	{
		struct Sound {
			enum class Group
			{
				bgm,
				custom,
				sfx,
				none,
			};

			std::string	name;
			std::string	path;
			std::string	hash;
			size_t		id;
			Group		group;

			Sound()
				: group(Group::none)
			{

			}

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
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive & ar, const unsigned int version)
			{
				ar & name;
				ar & path;
				ar & hash;
				ar & id;
				ar & group;
			}
		};
	}
}
#endif // INCLUDE_GUARD
