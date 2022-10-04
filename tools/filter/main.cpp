#include <iostream>
#include <functional>
#include <memory>
#include <queue>

// Hide error message reporting from CImg.
#define cimg_verbosity 0
#include "CImg.h"
#include "framework/FilterFactory.h"
#include "filter/gaussian.h"
#include "filter/versions/gaussian_v0.h"
#include "filter/versions/gaussian_v1.h"
#include "filter/versions/gaussian_v2.h"
#include "filter/versions/gaussian_v3.h"
#include "filter/versions/gaussian_v4.h"
#include "image/TestImages.h"
#include "util/PerformanceTest.h"
#include "util/string.h"
#include "options.h"
#include "config.h"

using namespace std;
using namespace cimg_library;

using Image = CImg<unsigned char>;
using LTS::util::PerformanceTest;


unique_ptr<Image> load_image(const string& input);
void save_image(const Image& image, const string& file_name);
void perform_test(const function<void()>& test_func, const Options& options);
LTS::filter::ImageKernel* create_kernel(const string& name, const Options& opts);


int main(int argc, char* argv[])
{
    auto opts = process_all_options(argc, argv);

    unique_ptr<Image> image {load_image(opts.input)};
    Image output(image->width(), image->height(), image->depth(), image->spectrum());

    #if USE_FACTORY

    LTS::framework::FilterFactory factory;
    auto filter = factory.create(opts.filter_spec);

    function<void()> test_func = ([&](){
        filter->process(image->data(), image->height(), image->width(), image->spectrum(), output.data());
    });

    #else

    unique_ptr<LTS::filter::ImageKernel> kernel;
    try {
        kernel = unique_ptr<LTS::filter::ImageKernel>{create_kernel(opts.filter, opts)};
    } catch (invalid_argument& e) {
        cout << e.what() << endl;
        exit(1);
    }

    function<void()> test_func = ([&](){
        kernel->process(image->data(), image->width(), image->height(), output.data(), image->spectrum());
    });

    #endif

    if (opts.test) {
        perform_test(test_func, opts);
    } else {
        test_func();
    }

    if (!opts.output_file.empty())
        save_image(output, opts.output_file);
}


unique_ptr<Image> load_image(const string& input)
{
    // Check if any standard test patterns were specified.
    if (LTS::util::starts_with(input, "vertical-lines")) {
        vector<string> elements = LTS::util::split(input, {',', '{', '}'});
        queue<string> q;
        for (auto& e : elements)
            q.push(e);

        q.pop();

        if (q.empty()) {
            cout << "width must be specified for vertical-lines" << endl;
            exit(1);
        }
        auto width = stoi(q.front());
        q.pop();

        if (q.empty()) {
            cout << "height must be specified for vertical-lines" << endl;
            exit(1);
        }
        auto height = stoi(q.front());
        q.pop();

        auto channels = 1;
        if (!q.empty()) {
            channels = stoi(q.front());
            q.pop();
        }

        auto image = make_unique<Image>(width, height, 1, channels);
        LTS::image::vertical_lines(image->data(), width, height, channels);
        return image;
    }

    try {
        return make_unique<Image>(input.c_str());
    } catch (CImgIOException&) {
        cerr << "Unable to open file '" << input << "'." << endl;
        exit(1);
    } catch (...) {
        cerr << "Unknown error occurred opening file '" << input << "'." << endl;
        exit(1);
    }
}


void save_image(const Image& image, const string& file_name)
{
    try {
        image.save(file_name.c_str());
    } catch (CImgIOException&) {
        cout << "Unable to save filtered output to file '" << file_name << "'." << endl;
        exit(1);
    } catch (...) {
        cout << "Unexpected error occurred." << endl;
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


LTS::filter::ImageKernel* create_kernel(const string& name, const Options& opts)
{
    if (LTS::util::starts_with(name, "gaussian")) {
        if (name == "gaussian")
            return new LTS::filter::GaussianKernel;
        if (name == "gaussian_v0")
            return new LTS::filter::versions::GaussianKernel_v0;
        if (name == "gaussian_v1")
            return new LTS::filter::versions::GaussianKernel_v1;
        if (name == "gaussian_v2")
            return new LTS::filter::versions::GaussianKernel_v2;
        if (name == "gaussian_v3")
            return new LTS::filter::versions::GaussianKernel_v3;
        if (name == "gaussian_v4")
            return new LTS::filter::versions::GaussianKernel_v4;
    }

    throw invalid_argument("unrecognized filter type");
}
