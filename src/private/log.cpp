#include "micro/log.h"

#include <raylib.h>
#include <flecs.h>

#include <cstdarg>
#include <cstdio>
#include <filesystem>

namespace micro::log
{
    void connect_raylib()
    {
        SetTraceLogCallback(+[](int logLevel, const char *text, va_list args)
                            {
            // raylib uses printf-style formatting
            char buffer[1024];
            vsnprintf(buffer, sizeof(buffer), text, args);

            // make raylib logs lowercase to match micro's style
            for (char *c = buffer; *c; ++c)
                if (*c >= 'A' && *c <= 'Z')
                    *c += 'a' - 'A';

            switch (logLevel)
            {
                case LOG_INFO:
                    info_cat("raylib", "{}", buffer);
                    break;
                case LOG_WARNING:
                    warn_cat("raylib", "{}", buffer);
                    break;
                case LOG_ERROR:
                case LOG_FATAL:
                    error_cat("raylib", "{}", buffer);
                    break;
                default:
                    break;
            } });
    }

    void connect_flecs()
    {
        static auto flecs_log_adapter = +[](int32_t level, const char *file,
                                            int32_t line, const char *msg)
        {
            std::string cpy = msg;
            for (char &c : cpy)
                if (c >= 'A' && c <= 'Z')
                    c += 'a' - 'A';

            if (level >= 1)
                debug_cat("flecs", "{}", cpy);
            else if (level == 0)
                info_cat("flecs", "{}", cpy);
            else if (level == -2)
                warn_cat("flecs", "{}", cpy);
            else if (level == -3)
                error_cat("flecs", "{}", cpy);
            else /* level == -4 */
                error_cat("flecs", "{} (FATAL)", cpy);
        };

        ecs_os_set_api_defaults();
        static ecs_os_api_t os_api = ecs_os_get_api();
        os_api.log_ = flecs_log_adapter;
        ecs_os_set_api(&os_api);

        ecs_log_enable_colors(false);
        ecs_log_set_level(0); // info/trace
    }

    void set_format()
    {
        spdlog::set_level(spdlog::level::trace); // Set global log level to trace

        // micro format. just nice simple output
        spdlog::set_pattern("%H:%M:%S.%e  %^%-8l%$ %v");
    }
}
