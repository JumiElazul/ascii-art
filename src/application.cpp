#include "application.h"
#include "ascii_parser.h"
#include "image.h"
#include <fstream>
#include <iostream>
#include <vector>

application::application(std::vector<image>&& images, parsed_args&& args)
    : _images(std::move(images)), _args(std::move(args))
{
}

void application::run()
{
    std::fstream out_file(_args.output_file, std::ios::out);
    int count = 0;
    for (const image& img : _images)
    {
        ++count;
        std::cout << "Image " << count << ":\n";
        out_file << "Image " << count << ":\n";

        ascii_parser parser(img, _args, out_file);
    }
}

