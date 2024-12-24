#include "argument_parser.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>

argument_parser::argument_parser(int argc, char** argv)
    : input_files(), output_file(), max_width(max_width), _argc(argc), _argv(argv) { }

int argument_parser::parse()
{
    try
    {
        boost::program_options::options_description desc("[ ascii-art ] usage");

        boost::program_options::positional_options_description p;
        p.add("input", -1);

        desc.add_options()
            ("help,H", "Produce help message")
            ("input,I", boost::program_options::value<std::vector<std::string>>(), "Name of input files to process into ascii")
            ("output,O", boost::program_options::value<std::string>()->default_value(default_output_path), "Name of output file to write to")
            ("width,W", boost::program_options::value<int>(), "Max width in characters of the output ascii")
            ("ramp,R", boost::program_options::value<int>()->default_value(0), "Ramp to use for ascii conversion, 0 for simple, 1 for complex");
        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::command_line_parser(_argc, _argv).options(desc).positional(p).run(), vm);
        boost::program_options::notify(vm);

        if (vm.count("help")) std::cout << desc << '\n';

        if (vm.count("input"))
        {
            input_files = vm["input"].as<std::vector<std::string>>();
        }

        if (vm.count("output"))
        {
            output_file = vm["output"].as<std::string>();
        }

        if (vm.count("width"))
        {
            max_width = vm["width"].as<int>();
        }

        if (vm.count("ramp"))
        {
            ramp = vm["ramp"].as<int>();
        }
        return 0;
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

void argument_parser::print_args() const
{
    std::cout << "- Input files -\n";
    for (const std::string& s : input_files)
        std::cout << s << " ";

    std::cout << "\n- Output file -\n" << output_file << '\n';
    std::cout << "- Max width -\n";
    std::cout << max_width << '\n';
}
