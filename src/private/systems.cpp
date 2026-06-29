#include "micro/model/components/transform.h"
#include "micro/model/components/lua.h"

#include "micro/systems.h"
#include "micro/window.h"
#include "micro/log.h"

#include <print>

namespace micro::systems
{
    void register_all(flecs::world &world)
    {
        world.system<micro::components::transform>()
            .kind(flecs::OnUpdate)
            .each([](flecs::entity e, micro::components::transform &t)
                  { micro::window::draw_rectangle(
                        static_cast<int>(t.position.x),
                        static_cast<int>(t.position.y),
                        static_cast<int>(t.scale.x),
                        static_cast<int>(t.scale.y),
                        micro::colour(0.0f, 0.0f, 1.0f, 1.0f)); });

        world.system<micro::components::lua>()
            .kind(flecs::OnUpdate)
            .each([](flecs::entity e, micro::components::lua &l)
                  { l.update(); });
    }
}