#include <iostream>
#include <chrono>
#include <functional>
#include <memory>

// Hide error message reporting from CImg.
#define cimg_verbosity 0
#include "CImg.h"
#include "filter/gaussian.h"
#include "util/PerformanceTest.h"
#include "options.h"

using namespace std;
using namespace cimg_library;

#define MULTI_THREADED 1

#if MULTI_THREADED
constexpr size_t NumOfRuns = 25;
#else
constexpr size_t NumOfRuns = 100;
#endif

using Image = CImg<unsigned char>;


int main(int argc, char* argv[])
{
    auto opts = process_all_options(argc, argv);

    unique_ptr<Image> image;
    try {
        image = make_unique<Image>(opts.input_file.c_str());
    } catch (...) {
        cerr << "Unable to open file '" << opts.input_file << "'." << endl;
        exit(1);
    }

    Image output(image->width(), image->height(), image->depth(), image->spectrum());

    //unique_ptr<LTS::util::PerformanceTest> pt;

    LTS::util::PerformanceTest pt {NumOfRuns, opts.report_file};

    LTS::filters::GaussianKernel filter;

    function<void()> test_func = ([&](){
        filter.process(image->data(), image->width(), image->height(), output.data(), image->spectrum());
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

    if (!opts.output_file.empty()) {
        output.save(opts.output_file.c_str());
    }
}
