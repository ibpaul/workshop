#include "options.h"
#include "cxxopts.hpp"
using namespace std;


cxxopts::Options program_options()
{
    cxxopts::Options options("filter", "Process input files with specified filter.");

    options.add_options()
            ("input", "The input file to run through the filter.", cxxopts::value<string>())
            ("output", "The output file to save the filtered data to.", cxxopts::value<string>())
            ("t,test", "Perform timing test on algorithm", cxxopts::value<string>())
            ("r,report", "Test report output file.", cxxopts::value<string>())
            ("h,help", "Print usage.");

    options.parse_positional({"input", "output"});

    options
            .positional_help("input")
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

    if (!result.count("input")) {
        cout << "input file not provided" << endl;
        exit(1);
    }
    opts.input_file = result["input"].as<string>();

    if (result.count("output")) {
        opts.output_file = result["output"].as<string>();
    }

    if (result.count("report")) {
        opts.report_file = result["report"].as<string>();
    }

    if (result.count("test")) {
        opts.test = true;

        auto test_params_str = result["test"].as<string>();



        //cout << "test_params: " << test_params << endl;
    }

    return opts;
}


Options process_all_options(int argc, char* argv[])
{
    auto options = program_options();
    auto result = options.parse(argc, argv);

    return process_options(result, options);
}
