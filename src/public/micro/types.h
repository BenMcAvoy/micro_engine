#pragma once

#include <string>
#include <array>

struct Vector2;
struct Vector3;
struct Color;

namespace micro
{
    struct vec2
    {
        float x, y;

        vec2() : x(0), y(0) {}
        vec2(float x, float y) : x(x), y(y) {}
        vec2(std::array<float, 2> arr) : x(arr[0]), y(arr[1]) {}

        ::Vector2 to_raylib() const;
        static vec2 from_raylib(const ::Vector2 &v);
        std::array<float, 2> to_array() const;
        std::string to_string() const;

        vec2 operator+(const vec2 &other) const;
        vec2 operator-(const vec2 &other) const;
        vec2 operator*(float scalar) const;
        vec2 operator/(float scalar) const;
    };

    struct vec3
    {
        float x, y, z;

        vec3() : x(0), y(0), z(0) {}
        vec3(float x, float y, float z) : x(x), y(y), z(z) {}
        vec3(std::array<float, 3> arr) : x(arr[0]), y(arr[1]), z(arr[2]) {}

        ::Vector3 to_raylib() const;
        static vec3 from_raylib(const ::Vector3 &v);
        std::array<float, 3> to_array() const;
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
        constexpr colour(std::array<float, 4> arr)
            : r(arr[0]), g(arr[1]), b(arr[2]), a(arr[3]) {}

        float r, g, b, a;

        ::Color to_raylib() const;
        static colour from_raylib(const ::Color &c);
        std::array<float, 4> to_array() const;
        std::string to_string() const;

        colour operator+(const colour &other) const;
        colour operator-(const colour &other) const;
        colour operator*(float scalar) const;
        colour operator/(float scalar) const;
    };
}