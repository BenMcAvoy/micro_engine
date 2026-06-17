#pragma once

#include <string>
#include <unordered_map>

namespace micro::helpers
{
    // heterogeneous unordered_map with std::string and std::string_view keys
    // allows storing owned strings but looking up with string_views without creating temporary strings
    template <typename ValueType>
    using heterogeneous_string_unordered_map = std::unordered_map<std::string, ValueType, std::hash<std::string_view>, std::equal_to<>>;
}