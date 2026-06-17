#include "micro/engine.h"
#include "micro/engine_impl.h"

#include "micro/model/assets/actor.h"
#include "micro/model/actor.h"

#include "micro/log.h"

namespace micro
{
    void engine::run()
    {
        window_.run();
    }

    engine::engine(std::string_view window_title, vec2 window_size)
        : window_(window_title, window_size), impl_(new impl())
    {
        log::info("initializing engine...");

        auto &lua = impl_->sol_state;

        lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::string, sol::lib::table);
        lua["print"] = [](const std::string &str)
        {
            log::info("\033[33mlua\033[0m {}", str);
        };

        lua.script(R"(
            print("lua state initialized successfully.")
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
        log::debug("running test...");

        /*auto lua_asset = assets::lua("print('hello from lua!')", "test.lua");
        impl_->assets.emplace("test", lua_asset);

        auto &queried = std::get<assets::lua>(impl_->assets.at("test"));

        auto comp_handle = impl_->lua_components.create(queried);
        auto comp = impl_->lua_components.get(comp_handle);*/

        try
        {
            assets::actor actor_asset("C:/Users/Ben/micro_engine/test_actor_spec.json");
        }
        catch (const std::exception &e)
        {
            log::error("Error loading actor asset: {}", e.what());
        }
    }

    void engine::spawn_actor(std::string_view spec_path)
    {
        log::debug("spawning actor from spec: {}", spec_path);

        assets::actor actor_asset(spec_path);
        impl_->assets.emplace(actor_asset.name, actor_asset);

        // TODO: create actor instance
        model::actor actor_instance(actor_asset);
        // log::debug("actor instance created @ {:p}", static_cast<void *>(&actor_instance));

        // TODO: real actor storage
        static std::vector<model::actor> actor_instances;
        actor_instances.emplace_back(std::move(actor_instance));

        log::debug("actor spawned successfully @ {:p}", static_cast<void *>(&actor_instances.back()));
    }

    engine &engine::get_instance()
    {
        if (engine::instance_ == nullptr)
        {
            throw std::runtime_error("Engine instance is not initialized.");
        }

        return *engine::instance_;
    }
}
