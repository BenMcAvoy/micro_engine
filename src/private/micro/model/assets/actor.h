#pragma once

#include "micro/model/components/transform.h"

#include <string>
#include <vector>
#include <optional>
#include <filesystem>

namespace micro::assets
{
    struct actor
    {
        actor(std::filesystem::path path);

        std::string name;

        bool enabled; // default: false

        std::vector<std::string> tags; // default: {}

        // initial component state described by the spec
        std::optional<components::transform> transform; // default: none
        std::optional<std::filesystem::path> script;    // path to lua script, default: none
    };
}
