#ifndef JUMI_ASCII_ART_APPLICATION_H
#define JUMI_ASCII_ART_APPLICATION_H
#include <vector>
#include "image.h"
#include "argument_parser.h"
#include "ascii_parser.h"

class application
{
public:
    application(std::vector<image>&& images, parsed_args&& args);
    void run();

private:
    std::vector<image> _images;
    parsed_args _args;
};

#endif

