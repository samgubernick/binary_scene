
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"

#include <string>

struct Texture {
	std::string name;
	std::string path;

	Texture() {

	}

	Texture(std::string name, std::string path)
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
