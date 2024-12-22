#ifndef JUMI_ASCII_ART_IMAGE_LOADER_H
#define JUMI_ASCII_ART_IMAGE_LOADER_H
#include <string>

struct image
{
    int width;
    int height;
    int color_channels;
    unsigned char* data;
};

class image_loader
{
public:
    image_loader(const std::string& image_path);
    ~image_loader();
    inline const image& img() const noexcept { return _img; }

private:
    image _img;
};

#endif
