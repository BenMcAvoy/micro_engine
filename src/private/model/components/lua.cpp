#include "micro/model/components/transform.h"
#include "micro/model/components/lua.h"
#include "micro/engine_impl.h"
#include "micro/log.h"

namespace micro::components
{
    lua::lua(assets::lua &asset_, flecs::entity entity)
        : entity_(entity)
    {
        log::debug("initializing lua component with asset: {}", asset_.path);

        sol::state &state = engine_lua_state();
        /*state.new_usertype<lua>("lua",
                                sol::no_constructor,
                                sol::meta_function::index,
                                [](lua &self, const std::string &key, sol::this_state ts) -> sol::object
                                {
                                    sol::state_view sv(ts);

                                    // get component from entity
                                    if (key == "transform")
                                    {
                                        return sol::make_object(sv, &self.entity_.get_mut<components::transform>());
                                    }
                                    else if (key == "lua")
                                    {
                                        return sol::make_object(sv, &self.entity_.get_mut<components::lua>());
                                    }
                                    else
                                    {
                                        log::error("unknown component key: {}", key);
                                        throw std::runtime_error("unknown component key: " + key);
                                    }
                                });*/

        sol::table table = state.create_table();

        state["script"] = table;
        auto res = state.safe_script_file(asset_.path, sol::script_pass_on_error);
        if (!res.valid())
        {
            sol::error err = res;
            log::error("error loading lua script from {}: {}", asset_.path, err.what());
        }

        auto load_func = table["load"];
        if (!load_func.valid() || load_func.get_type() != sol::type::function)
        {
            log::error("lua script {} does not have a valid 'load' function", asset_.path);
        }

        auto update_func = table["update"];
        if (!update_func.valid() || update_func.get_type() != sol::type::function)
        {
            log::error("lua script {} does not have a valid 'update' function", asset_.path);
        }

        auto draw_func = table["draw"];
        if (!draw_func.valid() || draw_func.get_type() != sol::type::function)
        {
            log::error("lua script {} does not have a valid 'draw' function", asset_.path);
        }

        load_func_ = load_func;
        update_func_ = update_func;
        draw_func_ = draw_func;

        log::debug("lua load {}, update {}, draw {}. functions loaded from {}", load_func.valid() ? "valid" : "invalid", update_func.valid() ? "valid" : "invalid", draw_func.valid() ? "valid" : "invalid", asset_.path);

        // call the load function to initialize the script
        sol::protected_function_result load_result = load_func(this);
        if (!load_result.valid())
        {
            sol::error err = load_result;
            log::error("error calling 'load' function in lua script {}: {}", asset_.path, err.what());
        }
    }

    lua::lua(std::string_view lua_asset_name, flecs::entity entity)
        : lua(get_asset_by_name(lua_asset_name), entity)
    {
    }

    void lua::update()
    {
        if (update_func_.valid())
        {
            sol::protected_function_result update_result = update_func_(this, window::get_frame_time());
            if (!update_result.valid())
            {
                sol::error err = update_result;
                log::error("error calling 'update' function in lua script: {}", err.what());
            }
        }
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
