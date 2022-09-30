#include <iostream>
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

using Image = CImg<unsigned char>;
using LTS::util::PerformanceTest;


unique_ptr<Image> load_image(const string& file_name);
void perform_test(const function<void()>& test_func, const Options& options);


int main(int argc, char* argv[])
{
    auto opts = process_all_options(argc, argv);

    unique_ptr<Image> image {load_image(opts.input_file)};
    Image output(image->width(), image->height(), image->depth(), image->spectrum());

    LTS::filters::GaussianKernel filter;

    function<void()> test_func = ([&](){
        filter.process(image->data(), image->width(), image->height(), output.data(), image->spectrum());
    });

    if (opts.test) {
        perform_test(test_func, opts);
    } else {
        test_func();
    }

    if (!opts.output_file.empty()) {
        try {
            output.save(opts.output_file.c_str());
        } catch (...) {
            cout << "Unable to save filtered output to file '" << opts.output_file << "'." << endl;
            exit(1);
        }
    }
}


unique_ptr<Image> load_image(const string& file_name)
{
    try {
        return make_unique<Image>(file_name.c_str());
    } catch (...) {
        cerr << "Unable to open file '" << file_name << "'." << endl;
        exit(1);
    }
}


void perform_test(const function<void()>& test_func, const Options& options)
{
    auto pt = make_unique<PerformanceTest>(options.num_test_cycles, options.report_file);

    if (options.num_test_threads == 1) {
        pt->test(test_func);
    } else if (options.num_test_threads > 1) {
        vector<function<void()>> test_funcs;
        for (int i = 0; i < options.num_test_threads; ++i)
            test_funcs.push_back(test_func);
        pt->test_threaded(test_funcs);
    } else {
        cout << "Unexpected error occurred." << endl;
        exit(1);
    }
}
