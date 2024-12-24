#ifndef JUMI_ASCII_ART_IMAGE_LOADER_H
#define JUMI_ASCII_ART_IMAGE_LOADER_H
#include <string>
#include <iosfwd>

class image
{
public:
    int width;
    int height;
    int color_channels;
    unsigned char* data;

    image(const std::string& image_path);
    ~image();
    image(const image& rhs) = delete;
    image& operator=(const image& rhs) = delete;
    image(image&& rhs) noexcept;
    image& operator=(image&& rhs) noexcept;

    void resize(int max_width);
};

std::ostream& operator<<(std::ostream& os, const image& img);

#endif
