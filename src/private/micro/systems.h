#pragma once

#include <flecs.h>

namespace micro::systems
{
    void register_all(flecs::world &world);
}