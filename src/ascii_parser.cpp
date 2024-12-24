#include "ascii_parser.h"
#include <cassert>
#include <iostream>
#include <fstream>

std::string ascii_parser::_ascii_ramp_simple = "@%#*+=-:. ";
std::string ascii_parser::_ascii_ramp_complex = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

ascii_parser::ascii_parser(const image& img, std::fstream& file, ascii_ramp ramp)
{
    const std::string& active_ramp = ramp == ascii_ramp::simple ? _ascii_ramp_simple : _ascii_ramp_complex;

    for (size_t row = 0; row < img.height; ++row)
    {
        for (size_t col = 0; col < img.width; ++col)
        {
            const size_t pixel_index = (row * img.width + col) * img.color_channels;
            const unsigned char r = img.data[pixel_index];
            const unsigned char g = img.data[pixel_index + 1];
            const unsigned char b = img.data[pixel_index + 2];
            const unsigned char gray = static_cast<unsigned char>(0.2126 * r + 0.6652 * g + 0.1222 * b);

            const size_t ramp_index = gray * active_ramp.size() / 256;

            assert(ramp_index >= 0);
            assert(ramp_index < active_ramp.size());

            const char ascii_char = active_ramp[ramp_index];
            std::cout << ascii_char;
            file << ascii_char;
        }
        std::cout << '\n';
        file << '\n';
    }
}
