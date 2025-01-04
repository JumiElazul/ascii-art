#include "application.h"
#include "argument_parser.h"
#include "image.h"
#include <iostream>
#include <vector>
#include <string>

#ifdef DEBUG
    #include "ascii_debug.h"
#endif

int main(int argc, char** argv)
{
#ifdef DEBUG
    scoped_timer timer("ascii-ast program execution time");
#endif
    argument_parser args(argc, argv);
    if (args.parse() != 0)
        return 1;

    parsed_args parsed_args = args.get_args();
    std::vector<image> images;
    images.reserve(parsed_args.input_files.size());

    for (const std::string& image_path : parsed_args.input_files)
    {
        image img(image_path, parsed_args);
        if (!img.data) continue;

        images.emplace_back(std::move(img));
    }

    application app(std::move(images), std::move(parsed_args));
    app.run();
}
