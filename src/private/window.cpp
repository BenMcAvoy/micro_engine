#include "micro/window.h"
#include "micro/types.h"

#include <raylib.h>

namespace micro
{

    void window::init()
    {
        InitWindow(width, height, title.c_str());
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
            end_drawing();
        }
    }
}