#include "application.h"
#include "ascii_parser.h"
#include "image.h"
#include <fstream>
#include <iostream>
#include <vector>

application::application(std::vector<image>&& images, const std::string& output_file, int ramp)
    : _images(std::move(images)), _output_file(output_file), _ramp(static_cast<ascii_ramp>(ramp))
{
}

void application::run()
{
    std::fstream file(_output_file, std::ios::out);
    int count = 0;
    for (const image& img : _images)
    {
        ++count;
        std::cout << "Image " << count << ":\n";
        file << "Image " << count << ":\n";

        ascii_parser parser(img, file, _ramp);
    }
}

