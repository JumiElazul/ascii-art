#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"
#include <iostream>

image::image(const std::string& image_path)
{
    data = stbi_load(image_path.c_str(), &width, &height, &color_channels, 0);
    if (!data)
    {
        std::cerr << "image with path={" << image_path << "} could not be loaded; doesn't exist?\n";
        return;
    }

    std::cout << "image with path={" << image_path << "} successfully loaded: " << *this << '\n';
}

image::~image()
{
    stbi_image_free(data);
}

image::image(image&& rhs) noexcept
    : width(rhs.width), height(rhs.height), color_channels(rhs.color_channels), data(rhs.data)
{
    rhs.width = 0;
    rhs.height = 0;
    rhs.color_channels = 0;
    rhs.data = nullptr;
}

image& image::operator=(image&& rhs) noexcept
{
    if (this != &rhs)
    {
        width = rhs.width;
        height = rhs.height;
        color_channels = rhs.color_channels;
        data = rhs.data;

        rhs.width = 0;
        rhs.height = 0;
        rhs.color_channels = 0;
        rhs.data = nullptr;
    }

    return *this;
}

std::ostream& operator<<(std::ostream& os, const image& img)
{
    os << "img={'width=" << img.width << "', height='" << img.height << "', num_channels='" << img.color_channels << "'}";
    return os;
}
