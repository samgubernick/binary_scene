
#ifndef SAM_BINARY_DATA_IS_MATCH_HPP_INCLUDED
#define SAM_BINARY_DATA_IS_MATCH_HPP_INCLUDED
#pragma once

#include <string>

namespace sam::binary_data {
auto is_match(
	std::string const & a,
	std::string const & b
) -> bool;

auto is_match(
	char a,
	char b
) -> bool;
}
#endif // INCLUDE_GUARD
