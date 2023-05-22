
#ifndef SAM_BINARY_DATA_GET_TEXT_ID_HPP_INCLUDED
#define SAM_BINARY_DATA_GET_TEXT_ID_HPP_INCLUDED
#pragma once

#include "id.hpp"

#include <string>

namespace sam { namespace binary_data {
extern auto getTextId(std::string const & name) -> Id;
}}
#endif // INCLUDE_GUARD
