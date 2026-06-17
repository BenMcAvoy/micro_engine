#pragma once

#include "micro/helpers.h"

#include "micro/window.h"

#include "micro/model/asset.h"

#include "micro/model/components/pool.h"
#include "micro/model/components/lua.h"

namespace sol
{
    class state;
}

namespace micro
{
    class engine
    {
    public:
        engine(std::string_view window_title, vec2 window_size);
        ~engine();

        void test();

        static engine *get_instance();

        void run();

    private:
        window window_;

        helpers::heterogeneous_string_unordered_map<asset> assets_;

        components::pool<components::lua> lua_components_;

        // internal implementation details hidden from the public interface
        // e.g. sol::state
        struct impl;
        impl *impl_;

        // global pointer to the engine instance, used for accessing the engine from other parts of the code
        static inline engine *instance_ = nullptr;

        friend class components::lua;
    };
}