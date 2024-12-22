#include "argument_parser.h"
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    std::vector<std::string> input_files;
    std::string output_file;

    argument_parser args(argc, argv, input_files, output_file);
    if (args.parse() != 0)
        return 1;

    args.print_args();
}
