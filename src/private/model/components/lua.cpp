#pragma once

#include "micro/model/components/lua.h"
#include "micro/engine.h"

#include <sol/sol.hpp>

#include <cstddef>
#include <print>

namespace micro
{
    struct engine::impl
    {
        sol::state sol_state;
    };
}

namespace micro::components
{
    lua::lua(assets::lua &lua_asset)
        : lua_asset(lua_asset)
    {
        auto p = micro::engine::get_instance()->impl_->sol_state.create_table();
        std::uintptr_t ptr = reinterpret_cast<std::uintptr_t>(&sol_table_);

        sol::table *data = reinterpret_cast<sol::table *>(this->sol_table_);
        memcpy(data, &p, sizeof(sol::table));
        sol::table &t = *data;

        t["source"] = lua_asset.source;
    }
}