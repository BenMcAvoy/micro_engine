#pragma once

#include "micro/model/asset.h"
#include "micro/model/assets/lua.h"

#include "micro/helpers.h"

#include <sol/sol.hpp>
#include <flecs.h>

#include <string_view>

namespace micro
{
    struct bindings;
}

namespace micro::components
{
    class lua
    {
    public:
        lua(assets::lua &asset_, flecs::entity entity);
        lua(std::string_view lua_asset_name, flecs::entity entity);

        void update();

    private:
        sol::function load_func_;
        sol::function update_func_;
        sol::function draw_func_;

        flecs::entity entity_; // the entity that this component is attached to

        // helper to get sol::state from engine instance
        sol::state &engine_lua_state() const;
        helpers::heterogeneous_string_umap<asset> &engine_assets();
        assets::lua &get_asset_by_name(std::string_view lua_asset_name);

        friend struct micro::bindings;
    };
}
