#include "ascii_parser.h"
#include <cassert>
#include <iostream>

std::string ascii_parser::_ascii_ramp0 = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
std::string ascii_parser::_ascii_ramp1 = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

ascii_parser::ascii_parser(const image& img)
{
    for (size_t row = 0; row < img.height; ++row)
    {
        for (size_t col = 0; col < img.width; ++col)
        {
            const size_t pixel_index = (row * img.width + col) * img.color_channels;
            const unsigned char r = img.data[pixel_index];
            const unsigned char g = img.data[pixel_index + 1];
            const unsigned char b = img.data[pixel_index + 2];
            const unsigned char gray = static_cast<unsigned char>(0.2126 * r + 0.7152 * g + 0.0722 * b);
            const size_t ramp_index = gray * _ascii_ramp.size() / 256;

            assert(ramp_index < _ascii_ramp.size());

            const char ascii_char = _ascii_ramp[ramp_index];
            std::cout << ascii_char;
        }
        std::cout << '\n';
    }
}
