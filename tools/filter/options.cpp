#include "options.h"
#include <cassert>
#include <queue>
#include "cxxopts.hpp"
#include "util/string.h"
using namespace std;


void process_test_options(cxxopts::ParseResult& result, Options& opts);
void process_type_options(cxxopts::ParseResult& result, Options& opts);


cxxopts::Options program_options()
{
    cxxopts::Options options("filter", "Process input files with specified filter.");

    options.add_options()
            ("input", "The input file to run through the filter.", cxxopts::value<string>())
            ("output", "The output file to save the filtered data to.", cxxopts::value<string>())
            ("t,test", "Perform timing test on algorithm", cxxopts::value<string>())
            ("type", "Filter type to use.", cxxopts::value<string>())
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
    opts.input = result["input"].as<string>();

    if (result.count("output")) {
        opts.output_file = result["output"].as<string>();
    }

    if (result.count("report")) {
        opts.report_file = result["report"].as<string>();
    }

    process_type_options(result, opts);

    if (result.count("test"))
        process_test_options(result, opts);

    assert(opts.num_test_threads > 0);
    assert(opts.num_test_cycles > 0);
    assert(!opts.filter_spec.empty());

    return opts;
}


void process_type_options(cxxopts::ParseResult& result, Options& opts)
{
    if (!result.count("type")) {
        cout << "Filter type must be provided." << endl;
        exit(1);
    }

    opts.filter_spec = result["type"].as<string>();
}


void process_test_options(cxxopts::ParseResult& result, Options& opts)
{
    opts.test = true;

    auto test_params_str = result["test"].as<string>();
    auto params = lts::util::split(test_params_str, ',');

    if (!params.empty()) {
        if (params.size() > 2) {
            cout << "Invalid number of arguments for --test parameter." << endl;
            exit(1);
        }

        try {
            opts.num_test_cycles = stoi(params[0]);
        } catch (...) {
            cout << "Unable to parse --test parameters." << endl;
            exit(1);
        }

        if (params.size() > 1) {
            try {
                opts.num_test_threads = stoi(params[1]);
            } catch (...) {
                cout << "Unable to parse --test parameters." << endl;
                exit(1);
            }
        }
    }
}


Options process_all_options(int argc, char* argv[])
{
    auto options = program_options();
    auto result = options.parse(argc, argv);

    return process_options(result, options);
}
