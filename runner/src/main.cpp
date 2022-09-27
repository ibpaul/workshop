#include <iostream>
#include <chrono>
#include "CImg.h"
using namespace cimg_library;
#include "filter/gaussian.h"
#include "util/PerformanceTest.h"


constexpr char TimeReportFile[] = "time-report.txt";
constexpr size_t NumOfRuns = 100;


int main()
{
    CImg<unsigned char> image("data/peppers.png");
    CImg<unsigned char> output(image.width(), image.height(), image.depth(), image.spectrum());

    LTS::util::PerformanceTest pt {NumOfRuns, TimeReportFile};

    LTS::filters::GaussianKernel filter;

    auto test_func = ([&](){
        filter.process(image.data(), image.width(), image.height(), output.data(), image.spectrum());
    });

    pt.test(test_func);

    output.save("output.png");

    return 0;
}
