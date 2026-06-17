#pragma once

#include <string>
#include <vector>

#include "micro/helpers.h"
#include "micro/model/asset.h"
#include "micro/model/assets/actor.h"

#include <flecs.h>

namespace micro::model
{
    class actor
    {
    public:
        actor(assets::actor &actor_asset);
        actor(std::string_view asset_name);

    private:
        std::string name_;
        bool enabled_;

        std::vector<std::string> tags_;

        flecs::entity entity_;

        // TODO: components (need to look into how to store components)

        helpers::heterogeneous_string_umap<asset> &engine_assets();
        assets::actor &get_asset_by_name(std::string_view actor_asset_name);
    };
}