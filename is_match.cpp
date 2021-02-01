
#include "is_match.hpp"

namespace cur = sam::binary_data;

namespace
{
	constexpr auto MATCH = int{ 0 };
}

bool cur::is_match(std::string const & a, std::string const & b)
{
	return a.compare(b) == MATCH;
}

bool cur::is_match(char a, char b)
{
	return a == b;
}
