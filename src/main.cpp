#include "micro/engine.h"

int main(int argc, char **argv)
{
    micro::engine engine("micro_runtime", {800, 600});

    engine.spawn_actor("res/test_actor_spec.json");
    engine.run();

    return 0;
}
