
#ifndef SAM_BINARY_SCENES_HPP_INCLUDED
#define SAM_BINARY_SCENES_HPP_INCLUDED
#pragma once

#include "scene.hpp"

#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/serialization/vector.hpp"

#include <vector>

namespace sam
{
	namespace binary
	{
		struct Scenes {
			std::vector<Scene> scenes;
		private:
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive & ar, const unsigned int version) {
				ar & scenes;
			}
		};
	}
}
#endif // INCLUDE_GUARD
