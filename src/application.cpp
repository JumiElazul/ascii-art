#include "application.h"
#include "ascii_parser.h"
#include "image.h"
#include <vector>

application::application(std::vector<image>&& images, const std::string& output_file)
    : _images(std::move(images)), _output_file(output_file)
{
}

void application::run(int ramp)
{
    for (const image& img : _images)
    {
        ascii_parser parser(img, static_cast<ascii_ramp>(ramp));
    }
}

