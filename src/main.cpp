#include "micro/engine.h"

#include <filesystem>
#include <print>

int main(int argc, char **argv)
{
    auto dir = std::filesystem::current_path().parent_path().parent_path().parent_path().parent_path();
    std::filesystem::current_path(dir);

    micro::engine engine("micro_runtime", {800, 600});

    try
    {
        engine.spawn_actor("test_actor_spec.json");
    }
    catch (const std::exception &e)
    {
        std::println("error spawning actor: {}", e.what());
    }

    engine.run();

    return 0;
}
