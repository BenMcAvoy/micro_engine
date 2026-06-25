#pragma once

#include <string>
#include <unordered_map>

namespace micro::helpers
{
    struct transparent_string_hash
    {
        using is_transparent = void;

        std::size_t operator()(std::string_view s) const noexcept
        {
            return std::hash<std::string_view>{}(s);
        }

        std::size_t operator()(const std::string &s) const noexcept
        {
            return std::hash<std::string_view>{}(s);
        }

        std::size_t operator()(const char *s) const noexcept
        {
            return std::hash<std::string_view>{}(s);
        }
    };

    // heterogeneous unordered_map with std::string and std::string_view keys
    // allows storing owned strings but looking up with string_views without creating temporary strings
    template <typename ValueType>
    using heterogeneous_string_unordered_map = std::unordered_map<std::string, ValueType, transparent_string_hash, std::equal_to<>>;
}