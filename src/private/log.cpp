#include "micro/log.h"

#include <raylib.h>

#include <cstdarg>
#include <cstdio>

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
                    info("{}", buffer);
                    break;
                case LOG_WARNING:
                    warn("{}", buffer);
                    break;
                case LOG_ERROR:
                case LOG_FATAL:
                    error("{}", buffer);
                    break;
                default:
                    break;
            } });
    }

    void set_format()
    {
        spdlog::set_level(spdlog::level::trace); // Set global log level to trace

        // micro format. just nice simple output
        spdlog::set_pattern("%H:%M:%S.%e  %^%-6l%$ %v");
    }
}
