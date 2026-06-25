#pragma once

#include "micro/model/assets/texture.h"

namespace micro::components
{
    class texture
    {
    public:
        texture(assets::texture &texture_asset);
        texture(std::string_view texture_asset_name);

    private:
        assets::texture &texture_asset_;
    };
}