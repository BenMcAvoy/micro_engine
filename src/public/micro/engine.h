#pragma once

#include "micro/window.h"
#include "micro/types.h"

#include <string_view>

namespace micro::detail
{
    // internal access seam — defined in src/private/micro/engine_impl.h.
    // forward-declared here only to grant friendship; names no implementation types.
    struct engine_access;
}

namespace micro
{
    class engine
    {
    public:
        engine(std::string_view window_title, vec2 window_size);
        ~engine();

        engine(const engine &) = delete;
        engine &operator=(const engine &) = delete;

        void test();

        static engine *get_instance();

        void run();

    private:
        window window_;

        // implementation details
        struct impl;
        impl *impl_;

        // global pointer to the engine instance, used for accessing the engine from other parts of the code
        static inline engine *instance_ = nullptr;

        friend struct detail::engine_access;
    };
}
