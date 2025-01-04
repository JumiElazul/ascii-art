#ifndef JUMI_ASCII_ART_IMAGE_LOADER_H
#define JUMI_ASCII_ART_IMAGE_LOADER_H
#include <string>
#include <iosfwd>

struct parsed_args;

class image
{
public:
    int width;
    int height;
    int color_channels;
    unsigned char* data;

    image(const std::string& image_path, const parsed_args& parsed_args);
    ~image();
    image(const image& rhs) = delete;
    image& operator=(const image& rhs) = delete;
    image(image&& rhs) noexcept;
    image& operator=(image&& rhs) noexcept;

private:
    std::pair<int, int> get_target_width_height(const parsed_args& parsed_args) const;
    void resize(int target_width, int target_height);
};

std::ostream& operator<<(std::ostream& os, const image& img);

#endif
