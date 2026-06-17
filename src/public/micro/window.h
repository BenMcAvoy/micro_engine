#include <string>

#include "micro/types.h"

namespace micro
{
    class window {
    public:
        window(std::string_view title, vec2 size)
            : width(size.x), height(size.y), title(title) { init(); }
        ~window();

        void init();
        void set_target_fps(int fps);
        bool should_close();
        void begin_drawing();
        void clear_background(colour color);
        void end_drawing();
        void close();
        void run();

    private:
        int width;
        int height;

        std::string title;
    };
}