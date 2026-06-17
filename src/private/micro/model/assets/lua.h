#pragma once

#include <string_view>
#include <filesystem>

namespace micro::assets
{
    struct lua
    {
        lua(std::string_view source, std::string_view path);
        lua(std::string_view path);
        lua(std::filesystem::path path);

        lua() = default;

        std::string source;
        std::string path;
    };
}