#ifndef JUMI_ASCII_ART_ARGUMENT_PARSER_H
#define JUMI_ASCII_ART_ARGUMENT_PARSER_H
#include <string>
#include <vector>

struct parsed_args
{
    std::vector<std::string> input_files;
    std::string output_file;
    int width;
    int height;
    float char_aspect_ratio;
    bool ramp;
    bool invert;
    bool flip_y;
    bool flip_x;
    bool color;
};

class argument_parser
{
static constexpr const char* const default_output_path = "output.txt";
public:
    argument_parser(int argc, char** argv);

    int parse();
    const parsed_args& get_args() const;
    void print_args() const;

private:
    parsed_args _parsed;
    int _argc;
    char** _argv;

    void verify_args(const parsed_args& args) const;
};

#endif
