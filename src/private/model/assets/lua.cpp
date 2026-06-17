#include "micro/model/assets/lua.h"

#include <fstream>
#include <stdexcept>
#include <string>

namespace micro::assets
{
    lua::lua(std::string_view source, std::string_view path)
        : source(source), path(path) {}

    lua::lua(std::filesystem::path path)
        : path(path.string())
    {
        std::ifstream file(path);

        if (file.is_open())
        {
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            source = content;
        }
        else
        {
            source = "";
            throw std::runtime_error("Could not open file: " + path.string());
        }
    }

    lua::lua(std::string_view source)
        : source(source), path("N/A") {}
}