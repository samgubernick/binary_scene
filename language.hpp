#ifndef SAM_BINARY_DATA_LANGUAGE_HPP_INCLUDED
#define SAM_BINARY_DATA_LANGUAGE_HPP_INCLUDED
#pragma once

#include "string.hpp"

#include "bitsery/serializer.h"
#include "bitsery/traits/string.h"
#include "bitsery/traits/vector.h"

namespace sam::binary_data {
struct Language
{
	Language()
		: id{0}
		, version{0}
	{}

	Language(
		std::string name,
		std::string text
	)
		: name{name}
		, text{text}
		, id{0}
		, version{0}
	{}
public:
	std::string name;
	std::string text;
	std::vector<String> strings;
	uint32_t id;
	std::string hash;
	uint16_t version;
private:
	friend class bitsery::Access;
	template<typename S>
	void serialize(S & s)
	{
		s.value2b(version);
		s.text1b(name, 512);
		s.text1b(text, 1024);
		s.container(strings, 1024);
		s.text1b(hash, 1024);
		s.value4b(id);
	}
};
}
#endif // INCLUDE_GUARD
