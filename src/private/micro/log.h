#pragma once

#include <spdlog/spdlog.h>

#include <utility>

namespace micro::log
{
    template <typename... Args>
    void debug(spdlog::format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::debug(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void info(spdlog::format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::info(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warn(spdlog::format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::warn(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void error(spdlog::format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::error(fmt, std::forward<Args>(args)...);
    }

    void set_format();
    void connect_raylib();
}