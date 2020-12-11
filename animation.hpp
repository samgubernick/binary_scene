
#ifndef SAM_BINARY_ANIMATION_HPP_INCLUDED
#define SAM_BINARY_ANIMATION_HPP_INCLUDED
#pragma once

#include "end_of_animation.hpp"
#include "texture.hpp"

#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/serialization/vector.hpp"

#include <string>
#include <vector>

namespace sam
{
	namespace binary
	{
		struct Animation {
			std::string name;
			std::vector<Texture> textures;
			double speedDefault;
			double speedSlow;
			EndOfAnimation endOfAnimation;

			Animation()
				: endOfAnimation(EndOfAnimation::stop)
				, name("")
				, speedDefault(0.0)
				, speedSlow(0.0)
			{ }

			Animation(std::string name)
				: name(name)
				, speedDefault(0.0)
				, speedSlow(0.0)
				, endOfAnimation(EndOfAnimation::stop)
			{ }

		private:
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive & ar, const unsigned int version) {
				ar & endOfAnimation;
				ar & name;
				ar & speedDefault;
				ar & speedSlow;
				ar & textures;
			}
		};
	}
}
#endif // INCLUDE_GUARD
