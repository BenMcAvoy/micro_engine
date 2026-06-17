#include "micro/types.h"

#include <format>

#include <raylib.h>

namespace micro
{
    Vector2 vec2::to_raylib() const
    {
        return {x, y};
    }

    vec2 vec2::from_raylib(const Vector2 &v)
    {
        return {v.x, v.y};
    }

    std::string vec2::to_string() const
    {
        return std::format("vec2({}, {})", x, y);
    }

    Vector3 vec3::to_raylib() const
    {
        return {x, y, z};
    }

    vec3 vec3::from_raylib(const Vector3 &v)
    {
        return {v.x, v.y, v.z};
    }

    std::string vec3::to_string() const
    {
        return std::format("vec3({}, {}, {})", x, y, z);
    }

    Color colour::to_raylib() const
    {
        return {static_cast<unsigned char>(r * 255), static_cast<unsigned char>(g * 255), static_cast<unsigned char>(b * 255), static_cast<unsigned char>(a * 255)};
    }

    colour colour::from_raylib(const Color &c)
    {
        return {c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, c.a / 255.0f};
    }

    std::string colour::to_string() const
    {
        return std::format("colour({}, {}, {}, {})", r, g, b, a);
    }
}