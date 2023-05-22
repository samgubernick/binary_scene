
#ifndef SAM_BINARY_DATA_STRINGS_HPP_INCLUDED
#define SAM_BINARY_DATA_STRINGS_HPP_INCLUDED
#pragma once

#include "string.hpp"

#include "bitsery/serializer.h"
#include "bitsery/traits/string.h"

#include <string>

namespace sam { namespace binary_data {
struct Strings
{
	Language language;

	std::vector<String> strings;
	std::string	name;
	std::string	hash;
	uint32_t	id;
	uint16_t	version;

	String()
		: id(0)
		, version(0)
	{ }

	String(Language language,
		   std::vector<String> strings)
		: name(name)
		, language(language)
		, strings(strings)
		, id(0)
		, version(0)
	{
		//hash = path;
		hash = name.append("hello");
	}
private:
	friend class bitsery::Access;
	template<typename S>
	void serialize(S & s)
	{
		s.value2b(version);
		s.object(language);
		s.value4b(id);
		s.container1b(strings, 1024);
	}
};
}
}
#endif // INCLUDE_GUARD
