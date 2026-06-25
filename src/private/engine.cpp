#include "micro/engine.h"
#include "micro/engine_impl.h"

#include <iostream>

namespace micro
{
    void engine::run()
    {
        window_.run();
    }

    engine::engine(std::string_view window_title, vec2 window_size)
        : window_(window_title, window_size), impl_(new impl())
    {
        std::cout << "Initializing engine..." << std::endl;

        auto &lua = impl_->sol_state;

        lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::string, sol::lib::table);
        lua["print"] = [](const std::string &str)
        {
            std::cout << str << std::endl;
        };

        lua.script(R"(
            print("Lua state initialized successfully.")
        )");

        engine::instance_ = this;
    }

    engine::~engine()
    {
        delete impl_;
        engine::instance_ = nullptr;
    }

    void engine::test()
    {
        auto lua_asset = assets::lua("print('Hello from Lua!')", "test.lua");
        impl_->assets.emplace("test", lua_asset);

        auto &queried = std::get<assets::lua>(impl_->assets.at("test"));

        auto comp_handle = impl_->lua_components.create(queried);
        auto comp = impl_->lua_components.get(comp_handle);
    }

    engine *engine::get_instance()
    {
        if (engine::instance_ == nullptr)
        {
            throw std::runtime_error("Engine instance is not initialized.");
        }

        return engine::instance_;
    }
}
