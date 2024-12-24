#ifndef JUMI_ASCII_ART_ARGUMENT_PARSER_H
#define JUMI_ASCII_ART_ARGUMENT_PARSER_H
#include <string>
#include <vector>

class argument_parser
{
static constexpr const char* const default_output_path = "output.txt";
public:
    std::vector<std::string> input_files;
    std::string output_file;
    int max_width;
    int ramp;

    argument_parser(int argc, char** argv);

    int parse();
    void print_args() const;

private:
    int _argc;
    char** _argv;
};

#endif
