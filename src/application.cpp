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
    bool force_overwrite = false;
    bool file_exists = std::filesystem::exists(_args.output_file);

    if (file_exists)
    {
        std::string input;
        std::cout << "Output file already exists.  Overwrite? (y/n): ";
        std::getline(std::cin, input);

        if (input == "y")
        {
            std::cout << "Overwriting filepath...\n";
            force_overwrite = true;
        }
    }

    std::fstream out_file;
    bool pass_file = false;
    if ((force_overwrite && file_exists) || !file_exists)
    {
        out_file.open(_args.output_file, std::ios::out);
        pass_file = true;
    }

    int count = 0;
    for (const image& img : _images)
    {
        ++count;
        std::cout << "Image " << count << ":\n";
        out_file << "Image " << count << ":\n";

        if (pass_file)
            ascii_parser parser(img, _args, &out_file);
        else
            ascii_parser parser(img, _args, nullptr);
    }
}

