#include "micro/bindings.h"

#include "micro/model/components/lua.h"
#include "micro/model/components/transform.h"

namespace micro
{
    void bindings::init(sol::state &lua, flecs::world &ecs_world)
    {
        lua.new_usertype<components::lua>("lua",
                                          sol::no_constructor,
                                          sol::meta_function::index,
                                          [](components::lua &self, const std::string &key, sol::this_state ts) -> sol::object
                                          {
                                              sol::state_view sv(ts);

                                              // get component from entity
                                              if (key == "transform")
                                              {
                                                  return sol::make_object(sv, &self.entity_.get_mut<components::transform>());
                                              }
                                              else if (key == "lua")
                                              {
                                                  return sol::make_object(sv, &self.entity_.get_mut<components::lua>());
                                              }
                                              else
                                              {
                                                  throw std::runtime_error("unknown component key: " + key);
                                              }
                                          });

        lua.new_usertype<components::transform>("transform",
                                                sol::no_constructor,
                                                "position", &components::transform::position,
                                                "scale", &components::transform::scale,
                                                "rotation", &components::transform::rotation);

        lua.new_usertype<vec2>("vec2",
                               sol::constructors<vec2(), vec2(float, float), vec2(std::array<float, 2>)>(),
                               "x", &vec2::x,
                               "y", &vec2::y);
        lua.new_usertype<vec3>("vec3",
                               sol::constructors<vec3(), vec3(float, float, float), vec3(std::array<float, 3>)>(),
                               "x", &vec3::x,
                               "y", &vec3::y,
                               "z", &vec3::z);
        lua.new_usertype<colour>("colour",
                                 sol::constructors<colour(), colour(float, float, float, float), colour(float), colour(std::array<float, 4>)>(),
                                 "r", &colour::r,
                                 "g", &colour::g,
                                 "b", &colour::b,
                                 "a", &colour::a);
    }
}