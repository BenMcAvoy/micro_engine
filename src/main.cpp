#include "micro/engine.h"

int main(int argc, char **argv)
{
    micro::engine engine("micro_runtime", {800, 600});

    engine.test();

    engine.run();

    return 0;
}
