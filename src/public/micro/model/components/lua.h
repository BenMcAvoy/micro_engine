#pragma once

#include "micro/model/assets/lua.h"

#include <cstddef>

// namespace sol
// {
//     class table;
//     class state;
// }

namespace micro::components
{
    class lua
    {
    public:
        lua(assets::lua &lua_asset);
        lua(std::string_view lua_asset_name);

    private:
        // asset source for script
        assets::lua &lua_asset;

        // opaque storage for sol::table
        alignas(16) std::byte sol_table_[16];
        // sol::table &get_sol_table();
    };
}