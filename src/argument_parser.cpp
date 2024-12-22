#include "argument_parser.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>

argument_parser::argument_parser(int argc, char** argv, std::vector<std::string>& input_files, std::string& output_file)
    : _argc(argc), _argv(argv), _input_files(input_files), _output_file(output_file) { }

int argument_parser::parse() const
{
    try
    {
        boost::program_options::options_description desc("[ ascii-art ] usage");

        boost::program_options::positional_options_description p;
        p.add("input", -1);

        desc.add_options()
            ("help,H", "Produce help message")
            ("input,I", boost::program_options::value<std::vector<std::string>>(), "Name of input files to process into ascii")
            ("output,O", boost::program_options::value<std::string>()->default_value(default_output_path), "Name of output file to write ascii to");

        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::command_line_parser(_argc, _argv).options(desc).positional(p).run(), vm);
        boost::program_options::notify(vm);

        if (vm.count("help")) std::cout << desc << '\n';

        if (vm.count("input"))
        {
            for (const std::string& s : vm["input"].as<std::vector<std::string>>())
            {
                _input_files.push_back(s);
            }
        }

        if (vm.count("output"))
        {
            _output_file = vm["output"].as<std::string>();
        }
        return 0;
    }
    catch (const boost::wrapexcept<boost::program_options::unknown_option>& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

void argument_parser::print_args() const
{
    std::cout << "- Input files -\n";
    for (const std::string& s : _input_files)
        std::cout << s << '\n';

    std::cout << "- Output file -\n" << _output_file << '\n';
}
