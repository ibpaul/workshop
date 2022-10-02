#include "options.h"
#include "cxxopts.hpp"
using namespace std;


void process_test_options(cxxopts::ParseResult& result, Options& opts);
void process_type_options(cxxopts::ParseResult& result, Options& opts);


cxxopts::Options program_options()
{
    cxxopts::Options options("filter", "Process input files with specified filter.");

    options.add_options()
        ("image-to-cpp", "Convert an image to C++ text.", cxxopts::value<bool>()->default_value("false"))
        ("option1", "Option #1. Dependant on the operation. Typically the input file.", cxxopts::value<string>())
        ("option2", "Option #2. Dependant on the operation. Typically the output file.", cxxopts::value<string>())
        ("h,help", "Print usage.");

    options.parse_positional({"option1", "option2"});

    options
        .positional_help("option1")
        .positional_help("option2")
        .show_positional_help();

    return options;
}


Options process_options(
    cxxopts::ParseResult& result,
    cxxopts::Options& options)
{
    Options opts {};

    if (result.count("help")) {
        cout << options.help() << endl;
        exit(0);
    }

    if (result.count("image-to-cpp")) {
        opts.operation = Options::Operation::ImageToCpp;

        if (!result.count("option1")) {
            cout << "input file required for operation" << endl;
            exit(1);
        }
        opts.string_param_0 = result["option1"].as<string>();

        if (!result.count("option2")) {
            cout << "output file required for operation" << endl;
            exit(1);
        }
        opts.string_param_1 = result["option2"].as<string>();

        opts.num_params_provided = 2;
    }

    return opts;
}


Options process_all_options(int argc, char* argv[])
{
    auto options = program_options();
    auto result = options.parse(argc, argv);

    return process_options(result, options);
}
