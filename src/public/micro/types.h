#pragma once

#include <string>

struct Vector2;
struct Vector3;
struct Color;

namespace micro
{
    struct vec2
    {
        float x, y;

        ::Vector2 to_raylib() const;
        static vec2 from_raylib(const ::Vector2 &v);
        std::string to_string() const;

        vec2 operator+(const vec2 &other) const;
        vec2 operator-(const vec2 &other) const;
        vec2 operator*(float scalar) const;
        vec2 operator/(float scalar) const;
    };

    struct vec3
    {
        float x, y, z;

        ::Vector3 to_raylib() const;
        static vec3 from_raylib(const ::Vector3 &v);
        std::string to_string() const;

        vec3 operator+(const vec3 &other) const;
        vec3 operator-(const vec3 &other) const;
        vec3 operator*(float scalar) const;
        vec3 operator/(float scalar) const;
    };

    struct colour
    {
        constexpr colour(float r, float g, float b, float a = 1.0f)
            : r(r), g(g), b(b), a(a) {}
        constexpr colour(float c)
            : r(c), g(c), b(c), a(1.0f) {}
        constexpr colour() : r(0), g(0), b(0), a(1) {}

        float r, g, b, a;

        ::Color to_raylib() const;
        static colour from_raylib(const ::Color &c);
        std::string to_string() const;

        colour operator+(const colour &other) const;
        colour operator-(const colour &other) const;
        colour operator*(float scalar) const;
        colour operator/(float scalar) const;
    };
}