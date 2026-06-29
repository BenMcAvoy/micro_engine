#pragma once

#include "micro/engine.h"

#include "micro/helpers.h"
#include "micro/model/asset.h"

#include "micro/model/components/lua.h"
#include "micro/model/components/texture.h"

#include <sol/sol.hpp>

#include <flecs.h>

namespace micro
{
    // internal engine implementation details
    struct engine::impl
    {
        sol::state sol_state;

        helpers::heterogeneous_string_umap<asset> assets;

        flecs::world ecs_world;
    };

    namespace detail
    {
        // helper struct to allow access to the engine's private implementation details from other parts of the code.
        struct engine_access
        {
            static engine::impl &of(engine &e) { return *e.impl_; }

            static sol::state &lua_state(engine &e) { return e.impl_->sol_state; }
            static flecs::world &ecs_world(engine &e) { return e.impl_->ecs_world; }
        };
    }
}
