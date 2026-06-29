#include "micro/engine.h"
#include "micro/engine_impl.h"

#include "micro/model/assets/actor.h"
#include "micro/model/components/lua.h"

#include "micro/systems.h"

#include "micro/log.h"

namespace micro
{
    void engine::run()
    {
        while (!window_.should_close())
        {
            window_.begin_drawing();
            window_.clear_background(colour(1.0f, 1.0f, 1.0f, 1.0f));

            impl_->ecs_world.progress();
            window_.draw_fps(10, 10);

            window_.end_drawing();
        }
    }

    engine::engine(std::string_view window_title, vec2 window_size)
        : window_(window_title, window_size), impl_(new impl())
    {
        log::info("initializing engine...");

        auto &world = impl_->ecs_world;

        world.import<flecs::stats>();
        world.set<flecs::Rest>({});

        systems::register_all(world);

        auto &lua = impl_->sol_state;

        lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::string, sol::lib::table);
        lua["print"] = [](const std::string &str)
        {
            log::info_cat("game", "{}", str);
        };

        lua.script(R"(
            print("hello from lua")
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
            log::error("error loading actor asset: {}", e.what());
        }
    }

    void engine::spawn_actor(std::string_view spec_path)
    {
        log::debug("spawning actor from spec: {}", spec_path);

        assets::actor actor_asset(spec_path);
        impl_->assets.emplace(actor_asset.name, actor_asset);

        auto entity = impl_->ecs_world.entity(actor_asset.name.c_str());

        for (auto &&component_variant : actor_asset.components)
        {
            std::visit([&](auto &&component)
                       {
                using T = std::decay_t<decltype(component)>;
                log::debug("adding component to actor entity: {}", typeid(component).name());
                if constexpr (std::is_same_v<T, assets::components::lua>)
                {
                    assets::lua lua_asset{component.path};
                    entity.emplace<components::lua>(lua_asset, entity);
                }
                else
                {
                    entity.set<T>(component);
                } },
                       component_variant);
        }
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
