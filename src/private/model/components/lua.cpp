#include "micro/model/components/lua.h"
#include "micro/engine_impl.h"

#include <stdexcept>

namespace micro::components
{
    lua::lua(assets::lua &asset_)
        : asset_(asset_)
    {
        ::micro::log::debug("initializing lua component with asset: {}", asset_.path);

        sol::state &state = engine_lua_state();

        table_ = state.create_table();

        table_["source"] = asset_.source;
        table_["path"] = asset_.path;

        state["script"] = table_;

        state.script("print(script.path)");
    }

    lua::lua(std::string_view lua_asset_name)
        : lua(get_asset_by_name(lua_asset_name))
    {
    }

    sol::state &lua::engine_lua_state() const
    {
        return detail::engine_access::lua_state(micro::engine::get_instance());
    }

    helpers::heterogeneous_string_umap<asset> &lua::engine_assets()
    {
        return detail::engine_access::of(micro::engine::get_instance()).assets;
    }

    assets::lua &lua::get_asset_by_name(std::string_view lua_asset_name)
    {
        auto &assets_map = engine_assets();

        auto it = assets_map.find(lua_asset_name);
        if (it == assets_map.end())
        {
            throw std::runtime_error("Lua asset not found: " + std::string(lua_asset_name));
        }

        return std::get<assets::lua>(it->second);
    }
}
