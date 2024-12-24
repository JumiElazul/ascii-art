#ifndef JUMI_ASCII_ART_APPLICATION_H
#define JUMI_ASCII_ART_APPLICATION_H
#include <vector>
#include "image.h"
#include "ascii_parser.h"

class application
{
public:
    application(std::vector<image>&& images, const std::string& output_file, int ramp);
    void run();

private:
    std::vector<image> _images;
    std::string _output_file;
    ascii_ramp _ramp;
};

#endif

