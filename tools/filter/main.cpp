#include <iostream>
#include <chrono>
#include <functional>

// Hide error message reporting from CImg.
#define cimg_verbosity 0
#include "CImg.h"
#include "cxxopts.hpp"
#include "filter/gaussian.h"
#include "util/PerformanceTest.h"

using namespace std;
using namespace cimg_library;

#define MULTI_THREADED 1
constexpr char TimeReportFile[] = "time-report.txt";

#if MULTI_THREADED
constexpr size_t NumOfRuns = 25;
#else
constexpr size_t NumOfRuns = 100;
#endif


cxxopts::Options program_options()
{
    cxxopts::Options options("filter", "Process input files with specified filter.");

    options.add_options()
        ("input", "The input file to run through the filter.", cxxopts::value<string>())
        ("output", "The output file to save the filtered data to.", cxxopts::value<string>())
        ("h,help", "Print usage.");

    options.parse_positional({"input", "output"});

    options
        .positional_help("input")
        .show_positional_help();

    return options;
}


int main(int argc, char* argv[])
{
    auto options =program_options();
    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        cout << options.help() << endl;
        exit(0);
    }

    if (!result.count("input")) {
        cout << "input file not provided" << endl;
        exit(1);
    }

    string filename {result["input"].as<string>()};

    try {
        CImg<unsigned char> image(filename.c_str());
        CImg<unsigned char> output(image.width(), image.height(), image.depth(), image.spectrum());

        LTS::util::PerformanceTest pt {NumOfRuns, TimeReportFile};

        LTS::filters::GaussianKernel filter;

        function<void()> test_func = ([&](){
            filter.process(image.data(), image.width(), image.height(), output.data(), image.spectrum());
        });

        #if MULTI_THREADED
        vector<function<void()>> test_funcs;
        test_funcs.push_back(test_func);
        test_funcs.push_back(test_func);
        test_funcs.push_back(test_func);
        test_funcs.push_back(test_func);
        pt.test_threaded(test_funcs);
        #else
        pt.test(test_func);
        #endif

        if (result.count("output")) {
            output.save(result["output"].as<string>().c_str());
        }

    } catch (...) {
        cerr << "Unable to open file '" << filename << "'." << endl;
        return 1;
    }

    return 0;
}
