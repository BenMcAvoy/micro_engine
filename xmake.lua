add_rules("mode.debug", "mode.release")

set_languages("c++23")

-- dont include windows bloat
if is_plat("windows") then
    add_defines("NOGDI", "NOUSER")
end

add_requires("raylib")
add_requires("sol2")
add_requires("nlohmann_json")
add_requires("json-schema-validator")
add_requires("spdlog")
add_requires("flecs")

add_moduledirs("xmake")

target("micro_engine")
    set_kind("static")
    add_files("src/private/**.cpp")
    add_includedirs("src/public", {public = true})
    add_includedirs("src/private")
    add_packages("raylib", "sol2", "nlohmann_json", "json-schema-validator", "spdlog", "flecs")

    before_build(function (target)
        import("modules.embed_file").embed_file("res/actor_spec_schema.json", target)
    end)

target("micro_runtime")
    set_kind("binary")
    add_files("src/*.cpp")
    add_deps("micro_engine")