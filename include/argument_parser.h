#ifndef JUMI_ASCII_ART_ARGUMENT_PARSER_H
#define JUMI_ASCII_ART_ARGUMENT_PARSER_H
#include <string>
#include <vector>

class argument_parser
{
static constexpr const char* const default_output_path = "output.txt";

public:
    argument_parser(int argc, char** argv, std::vector<std::string>& input_files, std::string& output_file);
    int parse() const;
    void print_args() const;

private:
    int _argc;
    char** _argv;
    std::vector<std::string>& _input_files;
    std::string& _output_file;
};

#endif
