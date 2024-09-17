
#ifndef SAM_BINARY_ASSET_HPP_INCLUDED
#define SAM_BINARY_ASSET_HPP_INCLUDED
#pragma once

#include "bitsery/serializer.h"

#include <string>

namespace sam::binary {
struct Asset
{
	Asset() { }

	Asset(
		std::string name,
		std::string path
	)
		: name{name}
		, path{path}
	{ }
public:
	std::string name;
	std::string path;
private:
	friend class bitsery::Access;
	template<typename S>
	void serialize(S & s)
	{
		s.ext(*this, bitsery::ext::Growable{}, [](S & s, Animation & o)
				{
					s.text1b(o.name, 512);
					s.text1b(o.path, 1024);
				}
		);
	}
};
}
#endif // INCLUDE_GUARD
