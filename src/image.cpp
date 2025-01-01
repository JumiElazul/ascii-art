#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#ifdef WIN32
#include "stb_image_resize.h"
#else
#include "stb_image_resize2.h"
#endif
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
        stbi_image_free(data);

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

void image::resize(int max_width)
{
    if (!data)
        return;

    if (width <= max_width)
        return;

    int new_width = max_width;
    float aspect_ratio = static_cast<float>(height) / static_cast<float>(width);
    int new_height = static_cast<int>(aspect_ratio * max_width);

    unsigned char* new_data = (unsigned char*)malloc(new_width * new_height * color_channels);
    if (!new_data)
    {
        std::cerr << "Failed to allocate memory for resized image.\n";
        return;
    }

#ifdef WIN32
    stbir_resize_uint8(
        data, width, height, 0,
        new_data, new_width, new_height, 0,
        color_channels
    );
#else
    stbir_resize_uint8_linear(
        data, width, height, 0,
        new_data, new_width, new_height, 0,
        color_channels
    );
#endif

    stbi_image_free(data);

    data = new_data;
    width = new_width;
    height = new_height;
}

std::ostream& operator<<(std::ostream& os, const image& img)
{
    os << "img={'width=" << img.width << "', height='" << img.height << "', num_channels='" << img.color_channels << "'}";
    return os;
}
