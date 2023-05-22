
#ifndef SAM_BINARY_DATA_STRING_HPP_INCLUDED
#define SAM_BINARY_DATA_STRING_HPP_INCLUDED
#pragma once

#include "face_name.hpp"
#include "id.hpp"

#include "bitsery/serializer.h"
#include "bitsery/traits/string.h"

#include <string>

namespace sam { namespace binary_data
{
struct String
{
	FaceName	faceName;
	uint8_t		faceSize;
	std::string	text;
	std::string	name;
	Id			id;
	std::string	hash;
	uint16_t	version;

	String()
		: id(Id::none)
		, faceSize(0)
		, faceName(FaceName::none)
		, version(0)
	{ }

	String(std::string	name,
		   FaceName		faceName,
		   uint8_t		faceSize,
		   std::string	text,
		   Id			id)
		: name(name)
		, faceName(faceName)
		, faceSize(faceSize)
		, text(text)
		, id(id)
		, version(0)
	{
		hash = name;
	}
private:
	friend class bitsery::Access;
	template<typename S>
	void serialize(S & s)
	{
		s.value2b(version);
		s.text1b(name, 512);
		s.text1b(hash, 1024);
		s.value1b(id);
		s.value1b(faceName);
		s.value1b(faceSize);
		s.text1b(text, 1024);
	}
};
}}
#endif // INCLUDE_GUARD
