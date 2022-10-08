#include <iostream>
#include <functional>
#include <memory>
#include <queue>
#include <map>

// Hide error message reporting from CImg.
#define cimg_verbosity 0
#include "CImg.h"
#include "framework/FilterFactory.h"
#include "filter/gaussian.h"
#include "image/patterns.h"
#include "util/PerformanceTest.h"
#include "util/string.h"
#include "options.h"
#include "config.h"
#include "filter/operations.h"

using namespace std;
using namespace cimg_library;

using Image = CImg<unsigned char>;
using lts::util::PerformanceTest;


unique_ptr<Image> load_image(const string& input);
void save_image(const Image& image, const string& file_name);
void perform_test(const function<void()>& test_func, const Options& options);


int main(int argc, char* argv[])
{
    auto opts = process_all_options(argc, argv);

    unique_ptr<Image> image {load_image(opts.input)};
    Image output(image->width(), image->height(), image->depth(), image->spectrum());

    lts::framework::FilterFactory factory;
    std::unique_ptr<lts::framework::IFilter> filter;

    try {
        filter = factory.create(opts.filter_spec, opts.threads);
    } catch (exception& e) {
        cout << e.what() << endl;
        exit(1);
    }

    function<void()> test_func = ([&](){
        filter->process(image->data(), image->height(), image->width(), image->spectrum(), output.data());
    });

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
    map<string, void(*)(uint8_t*, size_t, size_t, size_t)> patterns;
    patterns["vertical-lines"] = lts::image::vertical_lines;
    patterns["horizontal-lines"] = lts::image::horizontal_lines;

    auto elements = lts::util::split(input, {',', '{', '}'});

    // Check if any standard test patterns were specified.
    if (patterns.find(elements[0]) != patterns.end()) {
        queue<string> q;
        for (auto& e : elements)
            q.push(e);

        auto pattern = q.front();
        q.pop();

        if (q.empty()) {
            cout << "width must be specified for " << pattern << endl;
            exit(1);
        }
        auto width = stoi(q.front());
        q.pop();

        if (q.empty()) {
            cout << "height must be specified for " << pattern << endl;
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
        patterns[pattern](image->data(), width, height, channels);
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
