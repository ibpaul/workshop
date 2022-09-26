#include <iostream>
#include <string>
#include <chrono>
#include "gaussian.h"
#include "basic.h"
#include "TestImages.h"

#include "CImg.h"
#include "File.h"

using namespace cimg_library;


constexpr char TimeReportFile[] = "time-report.txt";


void process_cimg_image(const CImg<uint8_t>& input, uint8_t* output)
{
    // Make sure our image is formatted correctly for us.
    if (input.depth() != 1) throw std::invalid_argument("invalid image depth");
    if (input.spectrum() != 1) throw std::invalid_argument("invalid number of channels for image");

    return;
}


int main()
{
    CImg<unsigned char> image("data/peppers.png");
    CImg<unsigned char> output(image.width(), image.height(), image.depth(), image.spectrum());

    LTS::filters::GaussianKernel filter;

    auto begin = std::chrono::high_resolution_clock::now();

    LTS::utils::File timeReportFile(TimeReportFile, "w");

    fprintf(timeReportFile(), "IndividualRunTimes\n");

    for (int i = 0; i < 100; ++i) {
        auto sub_begin = std::chrono::high_resolution_clock::now();

        filter.process(image.data(), image.width(), image.height(), output.data(), image.spectrum());

        auto sub_end = std::chrono::high_resolution_clock::now();
        auto sub_diff = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(sub_end - sub_begin).count()) / 1000.0;

        fprintf(timeReportFile(), "%f ms\n", sub_diff);
    }


    auto end = std::chrono::high_resolution_clock::now();
    auto diff = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000.0 / 100.0;

    std::cout << "total time (ms): " << diff << std::endl;

    output.save("output.png");




    /*uint8_t filtered[100*100];

    std::cout << "Number of channels: " << image.spectrum() << std::endl;

    process_cimg_image(image, filtered);*/

    return 0;


	/*std::cout << "Hell2" << std::endl;
    std::cout << test_func() << std::endl;
    std::cout << test_func2() << std::endl;

    auto test = LTS::image::vertical_lines(100, 100);

    uint8_t filtered[100*100];
    LTS::filters::GaussianKernel filter;

    filter.process(&test[0], 100, 100, filtered);

    CImg<uint8_t> pattern(filtered,100, 100, 1, 1);
    pattern.save("output.png");

    //load_image();

    std::cout << "Is it working?" << std::endl;*/
}
