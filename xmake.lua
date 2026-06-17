add_rules("mode.debug", "mode.release")

set_languages("c++23")

add_requires("raylib")
add_requires("sol2")
add_requires("nlohmann_json")
add_requires("json-schema-validator")

target("micro_engine")
    set_kind("static")
    add_files("src/private/**.cpp")
    add_includedirs("src/public", {public = true})
    add_packages("raylib", "sol2", "nlohmann_json", "json-schema-validator")

target("micro_runtime")
    set_kind("binary")
    add_files("src/*.cpp")
    add_deps("micro_engine")