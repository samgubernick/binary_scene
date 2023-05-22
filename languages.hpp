#ifndef SAM_BINARY_DATA_LANGUAGES_HPP_INCLUDED
#define SAM_BINARY_DATA_LANGUAGES_HPP_INCLUDED
#pragma once

#include "language.hpp"

#include "bitsery/serializer.h"
#include "bitsery/traits/vector.h"

namespace sam { namespace binary_data {
struct Languages
{
	std::vector<Language> list;
	uint16_t	version;

	Languages()
		: version(0)
	{}

	Languages(std::vector<Language> list)
		: list(list)
		, version(0)
	{}
private:
	friend class bitsery::Access;
	template<typename S>
	void serialize(S & s)
	{
		s.value2b(version);
		s.container(list, 32);
	}
};
}
}
#endif // INCLUDE_GUARD
