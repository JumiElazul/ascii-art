#include "image_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

image_loader::image_loader(const std::string& image_path)
    : _img()
{
    _img.data = stbi_load(image_path.c_str(), &_img.width, &_img.height, &_img.color_channels, 0);
    if (!_img.data)
    {
        // do thing
    }
}

image_loader::~image_loader()
{
    stbi_image_free(_img.data);
}
