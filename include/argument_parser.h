#ifndef JUMI_ASCII_ART_ARGUMENT_PARSER_H
#define JUMI_ASCII_ART_ARGUMENT_PARSER_H
#include <string>
#include <vector>

class argument_parser
{
static constexpr const char* const default_output_path = "output.txt";
static constexpr int default_max_width = 80;
public:
    std::vector<std::string> input_files;
    std::string output_file;
    int max_width;

    argument_parser(int argc, char** argv, int max_width = default_max_width);

    int parse();
    void print_args() const;

private:
    int _argc;
    char** _argv;
};

#endif
