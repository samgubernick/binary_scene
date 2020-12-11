
#ifndef SAM_BINARY_SPRITE_HPP_INCLUDED
#define SAM_BINARY_SPRITE_HPP_INCLUDED
#pragma once

#include "animation.hpp"

#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/serialization/vector.hpp"

#include <string>
#include <vector>

namespace sam
{
	namespace binary {
		struct Sprite {
			std::string name;
			std::vector<Animation> animations;

			Sprite() {

			}

			Sprite(std::string name)
				: name(name) {

			}

		private:
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive & ar, const unsigned int version) {
				ar & name;
				ar & animations;
			}
		};
	}
}
#endif // INCLUDE_GUARD
