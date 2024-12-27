#include "application.h"
#include "argument_parser.h"
#include "image.h"
#include <vector>
#include <string>

int main(int argc, char** argv)
{
    argument_parser args(argc, argv);
    if (args.parse() != 0)
        return 1;

    parsed_args parsed_args = args.get_args();
    std::vector<image> images;
    images.reserve(parsed_args.input_files.size());

    for (const std::string& image_path : parsed_args.input_files)
    {
        image img(image_path);
        if (img.data)
        {
            if (parsed_args.max_width > 0 && img.width > parsed_args.max_width)
            {
                img.resize(parsed_args.max_width);
            }
            images.emplace_back(std::move(img));
        }
    }

    application app(std::move(images), std::move(parsed_args));
    app.run();
}
