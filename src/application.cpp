#include "application.h"
#include "ascii_parser.h"
#include "image.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>

application::application(std::vector<image>&& images, parsed_args&& args)
    : _images(std::move(images)), _args(std::move(args))
{
}

void application::run()
{
    // Check if the output file already exists so that we don't forcibly overwrite it
    if (std::filesystem::exists(_args.output_file))
    {
        std::string input;
        std::cout << "Output file already exists.  Overwrite? (y/n): ";
        std::getline(std::cin, input);

        if (input != "y")
        {
            std::cout << "Not overwriting, exiting...\n";
            return;
        }
    }

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

