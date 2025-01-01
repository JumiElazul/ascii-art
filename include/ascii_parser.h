#ifndef JUMI_ASCII_ART_ASCII_PARSER_H
#define JUMI_ASCII_ART_ASCII_PARSER_H
#include "image.h"
#include <fstream>

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
};

#endif
