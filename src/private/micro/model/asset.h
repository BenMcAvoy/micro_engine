#pragma once

#include "assets/lua.h"
#include "assets/texture.h"

#include <variant>

namespace micro
{
    using asset = std::variant<assets::lua, assets::texture>;
}