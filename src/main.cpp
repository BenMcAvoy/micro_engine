#include "micro/engine.h"

int main(int argc, char **argv)
{
    micro::engine engine("micro_runtime", {800, 600});

    // engine.test();

    engine.spawn_actor("C:/Users/Ben/micro_engine/test_actor_spec.json");

    engine.run();

    return 0;
}
