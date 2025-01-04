#include "image.h"
#include "argument_parser.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#ifdef WIN32
#include "stb_image_resize.h"
#else
#include "stb_image_resize2.h"
#endif
#include <iostream>

#ifdef DEBUG
    #include "ascii_debug.h"
#endif

image::image(const std::string& image_path, const parsed_args& parsed_args)
{
    data = stbi_load(image_path.c_str(), &width, &height, &color_channels, 0);
    if (!data)
    {
        std::cerr << "image with path={" << image_path << "} could not be loaded; doesn't exist?\n";
        return;
    }

    std::cout << "image with path={" << image_path << "} successfully loaded: " << *this << '\n';
    auto [target_width, target_height] = get_target_width_height(parsed_args);

    if (target_width != width || target_height != height)
    {
        std::cout << "Resizing image from " << width << "x" << height << " to " << target_width << "x" << target_height << '\n';
        resize(target_width, target_height);
    }
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

std::pair<int, int> image::get_target_width_height(const parsed_args& parsed_args) const
{
    bool user_specified_width =  (parsed_args.width != 0);
    bool user_specified_height = (parsed_args.height != 0);
    bool user_specified_char_aspect_ratio = (parsed_args.char_aspect_ratio >= 0.01f);

    float char_aspect_ratio = parsed_args.char_aspect_ratio;
    float img_height_f = static_cast<float>(height);
    float img_width_f = static_cast<float>(width);

    int target_width = 0;
    int target_height = 0;

    if (user_specified_width && user_specified_height)
    {
        target_width = parsed_args.width;
        target_height = parsed_args.height;
    }
    else if (user_specified_width)
    {
        target_width = parsed_args.width;
        float target_width_f = static_cast<float>(target_width);
        target_height = static_cast<int>(img_height_f * target_width_f / img_width_f);

        if (user_specified_char_aspect_ratio)
            target_height /= char_aspect_ratio;
    }
    else if (user_specified_height)
    {
        target_height = parsed_args.height;
        float target_height_f = static_cast<float>(target_height);
        target_width = static_cast<int>(img_width_f * target_height_f / img_height_f);

        if (user_specified_char_aspect_ratio)
            target_width *= char_aspect_ratio;
    }
    else
    {
        target_width = width;
        target_height = height;
    }

    return std::make_pair(target_width, target_height);
}

void image::resize(int new_width, int new_height)
{
#ifdef DEBUG
    scoped_timer timer("image::resize()");
#endif

    if (!data)
        return;

    if (new_width <= 0 || new_height <= 0)
        throw std::invalid_argument("new_width and new_height must be greater than 0");

    unsigned char* new_data = (unsigned char*)malloc(new_width * new_height * color_channels);
    if (!new_data)
        throw std::bad_alloc();

#ifdef WIN32
    stbir_resize_uint8(
        data, this->width, this->height, 0,
        new_data, new_width, new_height, 0,
        color_channels
    );
#else
    stbir_resize_uint8_linear(
        data, this->width, this->height, 0,
        new_data, new_width, new_height, 0,
        (stbir_pixel_layout)color_channels
    );
#endif

    stbi_image_free(data);

    data = new_data;
    this->width = new_width;
    this->height = new_height;
}

std::ostream& operator<<(std::ostream& os, const image& img)
{
    os << "img={'width=" << img.width << "', height='" << img.height << "', num_channels='" << img.color_channels << "'}";
    return os;
}
