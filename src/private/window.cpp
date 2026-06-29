#include "micro/window.h"
#include "micro/types.h"
#include "micro/log.h"

#include <raylib.h>

namespace micro
{
    window::window(std::string_view title, vec2 size)
        : width(size.x), height(size.y), title(title)
    {
        log::set_format();
        log::connect_raylib();
        log::connect_flecs();

        log::info("initializing window: {} ({}x{})", title, width, height);

        InitWindow(width, height, title.data());
    }

    window::~window()
    {
        CloseWindow();
    }

    void window::set_target_fps(int fps)
    {
        SetTargetFPS(fps);
    }

    bool window::should_close()
    {
        return WindowShouldClose();
    }

    void window::begin_drawing()
    {
        BeginDrawing();
    }

    void window::clear_background(colour color)
    {
        ClearBackground(color.to_raylib());
    }

    void window::draw_fps(int pos_x, int pos_y)
    {
        DrawFPS(pos_x, pos_y);
    }

    void window::draw_rectangle(int x, int y, int width, int height, colour color)
    {
        DrawRectangle(x, y, width, height, color.to_raylib());
    }

    float window::get_frame_time()
    {
        return GetFrameTime();
    }

    void window::end_drawing()
    {
        EndDrawing();
    }

    void window::close()
    {
        CloseWindow();
    }

    void window::run()
    {
        while (!WindowShouldClose())
        {
            begin_drawing();
            clear_background(colour(1.0f, 1.0f, 1.0f, 1.0f));
            draw_fps(10, 10);
            end_drawing();
        }
    }
}