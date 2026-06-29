#pragma once

#include <sol/sol.hpp>
#include <flecs.h>

namespace micro
{
    struct bindings
    {
        static void init(sol::state &lua_state, flecs::world &ecs_world);
    };
}