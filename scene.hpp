
#include "texture.hpp"

#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/serialization/vector.hpp"

#include <string>
#include <vector>

struct Scene {
	std::string name;
	std::vector<Texture> textures;

	Scene() {

	}

	Scene(std::string name)
		: name(name) {

	}

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & name;
		ar & textures;
	}
};
