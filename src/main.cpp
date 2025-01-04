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
        image img(image_path);
        if (!img.data) continue;

        bool user_specified_width =  (parsed_args.width != 0);
        bool user_specified_height = (parsed_args.height != 0);

        int target_width = 0;
        int target_height = 0;

        float char_aspect_ratio = parsed_args.char_aspect_ratio;
        float img_height_f = static_cast<float>(img.height);
        float img_width_f = static_cast<float>(img.width);

        if (user_specified_width && user_specified_height)
        {
            target_width = parsed_args.width;
            target_height = parsed_args.height;
        }
        else if (user_specified_width)
        {
            target_width = parsed_args.width;
            float target_width_f = static_cast<float>(target_width);
            target_height = static_cast<int>(img_height_f * target_width_f / img_width_f / char_aspect_ratio);
        }
        else if (user_specified_height)
        {
            target_height = parsed_args.height;
            float target_height_f = static_cast<float>(target_height);
            target_width = static_cast<int>(img_width_f * target_height_f / img_height_f * char_aspect_ratio);
        }
        else
        {
            target_width = img.width;
            target_height = img.height;
        }

        if (target_width != img.width || target_height != img.height)
        {
            std::cout << "Resizing image from " << img.width << "x" << img.height << " to " << target_width << "x" << target_height << '\n';
            img.resize(target_width, target_height);
        }

        images.emplace_back(std::move(img));
    }

    application app(std::move(images), std::move(parsed_args));
    app.run();
}
