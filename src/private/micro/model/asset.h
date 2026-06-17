#pragma once

#include "assets/actor.h"
#include "assets/lua.h"
#include "assets/texture.h"

#include <variant>

namespace micro
{
    using asset = std::variant<assets::actor, assets::lua, assets::texture>;
}