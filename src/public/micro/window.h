#include <string>

#include "micro/types.h"

namespace micro
{
    class window
    {
    public:
        window(std::string_view title, vec2 size);
        ~window();

        static void set_target_fps(int fps);
        static bool should_close();
        static void begin_drawing();
        static void clear_background(colour color);
        static void draw_rectangle(int x, int y, int width, int height, colour color);
        static void draw_fps(int pos_x, int pos_y);
        static void end_drawing();
        static void close();
        static void run();

    private:
        int width;
        int height;

        std::string title;
    };
}