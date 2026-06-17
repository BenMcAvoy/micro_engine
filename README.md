# micro engine

## overview

- micro engine is a small, lightweight, and flexible engine that can be used for a variety of purposes. it is designed to be easy to use and extend, and it provides a clean separation of concerns between the engine and the application that uses it.

## terminology

- spec: file on disk representing an actor, scene, etc ready to be created
- asset: a spec or other resource that has been loaded into memory and is ready to be used
- actor: an object in the scene that can be updated and rendered
- component: a piece of data that can be attached to an actor to give it behavior or properties
- script: a piece of code that can be attached to an actor to give it behavior
- scene: a collection of actors that can be updated and rendered together
- world: a collection of scenes that can be updated and rendered together

specs, assets, and actors compose the core of the engine.

## architecture

- the engine is intended to be a small, lightweight, and flexible engine that can be used for a variety of purposes
- you should include it as a library (as shown in `micro_runtime`) and the top level apis will be exposed to your applicaiton.
- micro engine only provides the headers and apis that are necessary to external applications, it does not expose internal implementation details. the internal implementation details are stored in private headers and source files that are not included in the library. this allows for a clean separation of concerns and makes it easier to maintain and update the engine without breaking external applications.

## usage

```cpp
#include "micro/engine.h"

int main(int argc, char **argv)
{
    micro::engine engine("micro_runtime", {800, 600});

    engine.run();

    return 0;
}
```

## building

this project utilizes [xmake](https://xmake.io/#/). to build the project, you will need to have xmake installed on your system. once you have xmake installed, you can build the project by running the following commands:

```bash
xmake f -p [platform] -a [architecture] -m [mode] # e.g. xmake f -p windows -a x64 -m release
xmake
```

## todo

- add actor management
- add component management (flecs style [dense, sparse, entity])
- add script environment loading
- add scene management
- add world management
- texture management
- screenshot of the engine in action
