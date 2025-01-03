#ifndef JUMI_ASCII_ART_ASCII_PARSER_H
#define JUMI_ASCII_ART_ASCII_PARSER_H
#include "image.h"
#include <iosfwd>

enum class ascii_ramp
{
    simple  = 0,
    complex = 1,
};

struct parsed_args;
class ascii_parser
{
public:
    ascii_parser(const image& img, const parsed_args& args, std::fstream& out_file);

private:
    std::string _ascii_ramp_simple;
    std::string _ascii_ramp_complex;

    unsigned char get_grayscale_value(unsigned char r, unsigned char g, unsigned char b) const noexcept;
    void write_char(std::fstream& file, char c);
    void write_char_color(std::fstream& file, char c, unsigned char r, unsigned char g, unsigned char b);
};

#endif
