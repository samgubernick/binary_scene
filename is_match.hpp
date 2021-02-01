
#ifndef SAM_BINARY_DATA_IS_MATCH_HPP_INCLUDED
#define SAM_BINARY_DATA_IS_MATCH_HPP_INCLUDED
#pragma once

#include <string>

namespace sam
{
	namespace binary_data
	{
		bool is_match(std::string const & a, std::string const & b);
		bool is_match(char a, char b);
	}
}
#endif // INCLUDE_GUARD
