#include <iostream>
#include <chrono>
#include <functional>
#include "CImg.h"
using namespace cimg_library;
#include "filter/gaussian.h"
#include "util/PerformanceTest.h"

#define MULTI_THREADED 1
constexpr char TimeReportFile[] = "time-report.txt";

#if MULTI_THREADED
constexpr size_t NumOfRuns = 25;
#else
constexpr size_t NumOfRuns = 100;
#endif


int main()
{
    CImg<unsigned char> image("data/peppers.png");
    CImg<unsigned char> output(image.width(), image.height(), image.depth(), image.spectrum());

    LTS::util::PerformanceTest pt {NumOfRuns, TimeReportFile};

    LTS::filters::GaussianKernel filter;

    std::function<void()> test_func = ([&](){
        filter.process(image.data(), image.width(), image.height(), output.data(), image.spectrum());
    });

    #if MULTI_THREADED
    std::vector<std::function<void()>> test_funcs;
    test_funcs.push_back(test_func);
    test_funcs.push_back(test_func);
    test_funcs.push_back(test_func);
    test_funcs.push_back(test_func);
    pt.test_threaded(test_funcs);
    #else
    pt.test(test_func);
    #endif

    output.save("output.png");

    return 0;
}
