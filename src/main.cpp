#include "argument_parser.h"
#include "image_loader.h"
#include <vector>
#include <string>

int main(int argc, char** argv)
{

    argument_parser args(argc, argv);
    if (args.parse() != 0)
        return 1;

    const std::vector<std::string>& input_files = args.input_files;
    const std::string& output_file = args.output_file;

    for (const std::string& image_path : input_files)
    {
        image_loader img(image_path);

    }

    args.print_args();
}
