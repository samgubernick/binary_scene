
#ifndef SAM_BINARY_ASSET_HPP_INCLUDED
#define SAM_BINARY_ASSET_HPP_INCLUDED
#pragma once

#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"

#include <string>

namespace sam
{
	namespace binary
	{
		struct Asset {
			std::string name;
			std::string path;

			Asset() {

			}

			Asset(std::string name, std::string path)
				: name(name)
				, path(path) {

			}

		private:
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive & ar, const unsigned int version) {
				ar & name;
				ar & path;
			}
		};
	}
}
#endif // INCLUDE_GUARD
