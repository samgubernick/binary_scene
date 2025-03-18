
#ifndef SAM_BINARY_DATA_SOUND_HPP_INCLUDED
#define SAM_BINARY_DATA_SOUND_HPP_INCLUDED
#pragma once

#include "bitsery/serializer.h"
#include "bitsery/traits/string.h"

#include <cstdint>
#include <string>

namespace sam::binary_data {
struct Sound
{
	enum class Group : int8_t
	{
		None,
		Bgm,
		Custom,
		Sfx,
	};

	Sound()
		: group{Group::None}
		, id{0}
		, version{0}
	{ }

	Sound(
		std::string name,
		std::string path,
		Group group
	)
		: hash{path}
		, name{name}
		, path{path}
		, id{0}
		, group{group}
		, version{0}
	{}
public:
	std::string name;
	std::string path;
	std::string hash;
	int32_t id;
	Group group;
	uint16_t version;
private:
	friend class bitsery::Access;
	template<typename S>
	auto serialize(S & s)
	{
		s.value2b(version);
		s.text1b(name, 512);
		s.text1b(path, 1024);
		s.text1b(hash, 1024);
		s.value4b(id);
		s.value1b(group);
	}
};
}
#endif // INCLUDE_GUARD
