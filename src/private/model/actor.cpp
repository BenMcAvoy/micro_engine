#include "micro/model/actor.h"
#include "micro/engine_impl.h"
#include "micro/log.h"

#include <variant>
#include <stdexcept>

namespace micro::model
{
    actor::actor(assets::actor &actor_asset)
        : name_(actor_asset.name), enabled_(actor_asset.enabled), tags_(actor_asset.tags)
    {
        auto &engine = micro::engine::get_instance();
        auto &ecs_world = detail::engine_access::ecs_world(engine);

        entity_ = ecs_world.entity(name_.c_str());

        for (auto &&component_variant : actor_asset.components)
        {
            std::visit([this](auto &&component)
                       {
                ::micro::log::debug("adding component to actor entity: {}", typeid(component).name());
                using T = std::decay_t<decltype(component)>;
                entity_.set<T>(component); },
                       component_variant);
        }
    }

    actor::actor(std::string_view actor_asset)
        : actor(get_asset_by_name(actor_asset))
    {
    }

    helpers::heterogeneous_string_umap<asset> &actor::engine_assets()
    {
        return detail::engine_access::of(micro::engine::get_instance()).assets;
    }

    assets::actor &actor::get_asset_by_name(std::string_view actor_asset_name)
    {
        auto &assets_map = engine_assets();

        auto it = assets_map.find(actor_asset_name);
        if (it == assets_map.end())
        {
            throw std::runtime_error("actor asset not found: " + std::string(actor_asset_name));
        }

        return std::get<assets::actor>(it->second);
    }
}