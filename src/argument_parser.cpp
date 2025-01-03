#include "argument_parser.h"
#include <boost/program_options.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <iostream>
#include <string>
#include <vector>

argument_parser::argument_parser(int argc, char** argv)
    : _parsed(), _argc(argc), _argv(argv) { }

int argument_parser::parse()
{
    if (_argc < 2) {
        std::cout << "[ ascii-art ]\n";
        std::cout << "Run with --help for details.\n";
        return 1;
    }

    try
    {
        boost::program_options::options_description desc("[ ascii-art ] usage");

        boost::program_options::positional_options_description p;
        p.add("input", -1);

        desc.add_options()
            ("help,h", "Produce help message")
            ("input,I", boost::program_options::value<std::vector<std::string>>(), "Name of input files to process into ascii")
            ("output,O", boost::program_options::value<std::string>()->default_value(default_output_path), "Name of output file to write to")
            ("width,W", boost::program_options::value<int>(), "Width in characters of the output ascii.  If height is not set, aspect ratio will be maintained")
            ("height,H", boost::program_options::value<int>(), "Height in characters of the output ascii. If width is not set, aspect ratio will be maintained")
            ("ramp,R", boost::program_options::bool_switch(&_parsed.ramp)->default_value(false), "When set, use a more complicated ramp for ascii calculation")
            ("invert,N", boost::program_options::bool_switch(&_parsed.invert)->default_value(false), "Inverts the ascii-calculation so that dark pixels are the lightest and vice versa")
            ("flip-y,Y", boost::program_options::bool_switch(&_parsed.flip_y)->default_value(false), "Flips the image vertically")
            ("flip-x,X", boost::program_options::bool_switch(&_parsed.flip_x)->default_value(false), "Flips the image horizontally")
            ("color,C", boost::program_options::bool_switch(&_parsed.color)->default_value(false), "Retains the color and produces a colored ascii image")
            ("char-aspect-ratio,A", boost::program_options::value<float>(&_parsed.char_aspect_ratio)->default_value(2.0f), "Aspect ratio of how much taller than wide the terminal characters are "
             "for ascii conversion, since most terminal characters are taller than wide. 2.0 is the default, and will mean than for every 2 characters wide, the terminal is 1 character tall.  "
             "This will not take effect when width and height are both set");
        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::command_line_parser(_argc, _argv).options(desc).positional(p).run(), vm);
        boost::program_options::notify(vm);

        if (vm.count("help")) std::cout << desc << '\n';

        if (vm.count("input"))  _parsed.input_files = vm["input"].as<std::vector<std::string>>();
        if (vm.count("output")) _parsed.output_file = vm["output"].as<std::string>();
        if (vm.count("width"))  _parsed.width = vm["width"].as<int>();
        if (vm.count("height")) _parsed.height = vm["height"].as<int>();
        if (vm.count("char-aspect-ratio")) _parsed.char_aspect_ratio = vm["char-aspect-ratio"].as<float>();

        try
        {
            verify_args(_parsed);
            return 0;
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
            return 1;
        }
    }
    catch (const boost::wrapexcept<boost::program_options::unknown_option>& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    catch (...) 
    {
        std::cerr << "Exception swallower\n";
        return 1; 
    }
}

const parsed_args& argument_parser::get_args() const
{
    return _parsed;
}

void argument_parser::print_args() const
{
    std::cout << "Input files={";
    for (const std::string& s : _parsed.input_files)
        std::cout << s << " ";

    std::cout << "}";

    std::cout << " Output file={" << _parsed.output_file << "}";
    std::cout << " Max width={" << _parsed.width << "}";
    std::cout << " Ramp={" << _parsed.ramp << "}";
    std::cout << " Invert={" << _parsed.invert << "}";

    std::cout << '\n';
}

void argument_parser::verify_args(const parsed_args& args) const
{
    if (args.width  < 0) throw std::invalid_argument("Width must be greater than 0");
    if (args.height < 0) throw std::invalid_argument("Height must be greater than 0");
}
