#include "ascii_parser.h"
#include "argument_parser.h"
#include <fmt/color.h>
#include <fmt/ostream.h>
#include <algorithm>
#include <cassert>
#include <fstream>

#ifdef DEBUG
    #include "ascii_debug.h"
#endif

ascii_parser::ascii_parser(const image& img, const parsed_args& args, std::fstream& out_file)
    : _ascii_ramp_simple("@%#*+=-:. ")
    , _ascii_ramp_complex("$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ")
    , _args(args)
{
#ifdef DEBUG
    scoped_timer timer("ascii_parser::ascii_parser()");
#endif

    std::string& active_ramp = args.ramp ? _ascii_ramp_complex : _ascii_ramp_simple;
    if (args.invert)
        std::reverse(active_ramp.begin(), active_ramp.end());

    bool flip_x = args.flip_x;
    bool flip_y = args.flip_y;

    for (size_t row = 0; row < img.height; ++row)
    {
        const size_t actual_row = args.flip_y ? (img.height - 1 - row) : row;

        for (size_t col = 0; col < img.width; ++col)
        {
            const size_t actual_col = args.flip_x ? (img.width - 1 - col) : col;

            const size_t pixel_index = (actual_row * img.width + actual_col) * img.color_channels;
            const unsigned char r = img.data[pixel_index];
            const unsigned char g = img.data[pixel_index + 1];
            const unsigned char b = img.data[pixel_index + 2];

            const unsigned char gray = get_grayscale_value(r, g, b);
            const size_t ramp_index = gray * active_ramp.size() / 256;

#ifdef DEBUG
            assert(ramp_index >= 0);
            assert(ramp_index < active_ramp.size());
#endif

            const char ascii_char = active_ramp[ramp_index];

            args.color ? write_char_color(out_file, ascii_char, r, g, b) : write_char(out_file, ascii_char);
        }
        write_char(out_file, '\n');
    }
}

unsigned char ascii_parser::get_grayscale_value(unsigned char r, unsigned char g, unsigned char b) const noexcept
{
    return static_cast<unsigned char>(0.2126 * r + 0.6652 * g + 0.1222 * b);
}

void ascii_parser::write_char(std::fstream& out_file, char ascii_char)
{
    if (!_args.disable_console)
        fmt::print("{}", ascii_char);
    fmt::print(out_file, "{}", ascii_char);
}

void ascii_parser::write_char_color(std::fstream& out_file, char ascii_char, unsigned char r, unsigned char g, unsigned char b)
{
    if (!_args.disable_console)
        fmt::print(fg(fmt::rgb(r, g, b)), "{}", ascii_char);
    fmt::print(out_file, "{}", ascii_char);
}
