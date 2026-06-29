#pragma once

#include "micro/types.h"
#include "micro/model/assets/lua.h"

#include <string>
#include <vector>
#include <variant>
#include <filesystem>

namespace micro::assets
{
    namespace components
    {
        struct transform
        {
            vec2 position;
            vec2 scale;
            int rotation;
        };

        struct lua
        {
            lua(assets::lua &asset_);

            std::filesystem::path path;
        };
    };

    using component = std::variant<components::transform, components::lua>;

    struct actor
    {
        actor(std::filesystem::path path);

        std::string name;

        bool enabled; // default: false

        std::vector<std::string> tags;     // default: {}
        std::vector<component> components; // default: {}
    };
}