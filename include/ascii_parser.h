#ifndef JUMI_ASCII_ART_ASCII_PARSER_H
#define JUMI_ASCII_ART_ASCII_PARSER_H
#include "image.h"

enum class ascii_ramp
{
    simple  = 0,
    complex = 1,
};

class ascii_parser
{
static std::string _ascii_ramp_simple;
static std::string _ascii_ramp_complex;
public:
    ascii_parser(const image& img, ascii_ramp ramp = ascii_ramp::simple);
};

#endif
