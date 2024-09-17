
#include "is_match.hpp"

namespace sam::binary_data {
namespace
{
constexpr auto MATCH = int{ 0 };
}

bool is_match(
	std::string const & a,
	std::string const & b
)
{
	return a.compare(b) == MATCH;
}

bool is_match(char a, char b)
{
	return a == b;
}
}
