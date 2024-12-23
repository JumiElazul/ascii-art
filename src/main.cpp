#include "application.h"
#include "argument_parser.h"
#include "image_loader.h"
#include <vector>
#include <string>

int main(int argc, char** argv)
{

    argument_parser args(argc, argv);
    if (args.parse() != 0)
        return 1;

    args.print_args();

    const std::vector<std::string>& input_files = args.input_files;
    const std::string& output_file = args.output_file;
    std::vector<image> images;
    images.reserve(input_files.size());

    for (const std::string& image_path : input_files)
    {
        image img(image_path);
        if (img.data)
        {
            images.emplace_back(std::move(img));
        }
    }

    application app(std::move(images));
}
