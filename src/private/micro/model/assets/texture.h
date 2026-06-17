#pragma once

#include <string>
#include <vector>

namespace micro::assets
{
    struct texture
    {
        // TODO: constructor with asset

        std::string path;

        std::vector<unsigned char> data;

        int width;
        int height;

        int channels;
    };
}