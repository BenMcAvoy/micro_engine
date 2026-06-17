#pragma once

#include <string>
#include <vector>

namespace micro::assets
{
    struct texture
    {
        std::string path;

        std::vector<unsigned char> data;

        int width;
        int height;

        int channels;
    };
}