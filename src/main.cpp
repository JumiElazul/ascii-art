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

    const std::vector<std::string>& input_files = args.input_files;
    const std::string& output_file = args.output_file;
    std::vector<image> images;
    int max_width = args.max_width;
    int ramp = args.ramp;

    images.reserve(input_files.size());

    for (const std::string& image_path : input_files)
    {
        image img(image_path);
        if (img.data)
        {
            if (max_width > 0 && img.width > max_width)
            {
                img.resize(max_width);
            }
            images.emplace_back(std::move(img));
        }
    }

    application app(std::move(images), output_file, ramp);
    app.run();
}
