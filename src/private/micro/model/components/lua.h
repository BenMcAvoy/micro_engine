#pragma once

#include "micro/model/asset.h"
#include "micro/model/assets/lua.h"

#include "micro/helpers.h"

#include <sol/sol.hpp>

#include <string_view>

namespace micro::components
{
    class lua
    {
    public:
        lua(assets::lua &asset_);
        lua(std::string_view lua_asset_name);

    private:
        // asset source for script
        assets::lua &asset_;

        // table handle for script state
        sol::table table_;

        // helper to get sol::state from engine instance
        sol::state &engine_lua_state() const;
        helpers::heterogeneous_string_umap<asset> &engine_assets();
        assets::lua &get_asset_by_name(std::string_view lua_asset_name);
    };
}
