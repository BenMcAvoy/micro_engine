#include "micro/model/assets/actor.h"
#include "micro/gen/actor_spec_schema.h"
#include "micro/log.h"

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include <fstream>
#include <string>

namespace micro::assets
{
    components::lua::lua(assets::lua &asset_)
        : path(asset_.path)
    {
    }

    actor::actor(std::filesystem::path path)
    {
        log::debug("loading actor spec");

        std::ifstream file(path);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open actor spec file: " + path.string());
        }

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        nlohmann::json json = nlohmann::json::parse(content);

        nlohmann::json_schema::json_validator validator;
        auto actor_spec_schema = nlohmann::json::parse(gen::actor_spec_schema);
        validator.set_root_schema(actor_spec_schema);
        log::debug("readied actor schema validator");

        validator.validate(json);

        log::debug("actor spec validated successfully");

        // extract required data
        name = json.value("name", "");
        enabled = json.value("enabled", true);
        tags = json.value("tags", std::vector<std::string>{});

        auto components_json = json["components"];
        std::optional<std::string> deferred_script_path;

        for (auto it = components_json.begin(); it != components_json.end(); ++it)
        {
            const std::string &component_name = it.key();
            const nlohmann::json &component_data = it.value();

            if (component_name == "transform")
            {
                components::transform transform_component;
                transform_component.position = {component_data["position"][0], component_data["position"][1]};
                transform_component.scale = {component_data["scale"][0], component_data["scale"][1]};
                transform_component.rotation = component_data["rotation"];
                components.emplace_back(transform_component);
                log::debug("extracted transform component");
            }
            else if (component_name == "script")
            {
                deferred_script_path = component_data["path"].get<std::string>();
            }
            else
            {
                log::warn("unknown component type: {}", component_name);
            }
        }

        // processed script last (everything else should be initialized first)
        if (deferred_script_path)
        {
            assets::lua lua_asset{std::filesystem::path{*deferred_script_path}};
            components::lua lua_component(lua_asset);
            components.emplace_back(lua_component);
            log::debug("extracted script component with path: {}", lua_component.path.string());
        }

        log::info("actor spec loaded successfully: {}", name);
    }
}