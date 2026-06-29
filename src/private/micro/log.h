#pragma once

#include <spdlog/spdlog.h>

#include <utility>

namespace micro::log
{
    template <typename... Args>
    void debug(spdlog::format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::debug("\033[33m{:<6}\033[0m {}", "micro", fmt::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void info(spdlog::format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::info("\033[33m{:<6}\033[0m {}", "micro", fmt::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void warn(spdlog::format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::warn("\033[33m{:<6}\033[0m {}", "micro", fmt::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void error(spdlog::format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::error("\033[33m{:<6}\033[0m {}", "micro", fmt::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void debug_cat(std::string_view cat, spdlog::format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::debug("\033[33m{:<6}\033[0m {}", cat, fmt::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void info_cat(std::string_view cat, spdlog::format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::info("\033[33m{:<6}\033[0m {}", cat, fmt::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void warn_cat(std::string_view cat, spdlog::format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::warn("\033[33m{:<6}\033[0m {}", cat, fmt::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void error_cat(std::string_view cat, spdlog::format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::error("\033[33m{:<6}\033[0m {}", cat, fmt::format(fmt, std::forward<Args>(args)...));
    }

    void set_format();
    void connect_raylib();
    void connect_flecs();
}