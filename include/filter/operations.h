// Common filtering operations.

#ifndef LTS_FILTER_OPERATIONS_H
#define LTS_FILTER_OPERATIONS_H

#include <cstddef>
#include <memory>
#include <future>
#include <vector>
#include "filter/Kernel.h"

namespace lts {
namespace filter {


// Performs a convolution on the input data using the supplied filter kernel.
//
// [parameters]
// kernel - The prefilled kernel.
// input - The input data to process.
// ncols - Number of cols of the input data (e.g. the image's width)
// nrows - Number of rows of the input data (e.g. the image's height)
// channels - Number of channels in the input data (e.g. 3 for RGB images).
// output - Output of the processed data. May be provided to the function uninitialized.
//
// [notes]
//  - This convolution implementation may not be mathematically pure since it does not involve
//    flipping of the kernel's matrix.
template<typename Tkernel, size_t Mkernel, size_t Nkernel>
void convolute(
    const KernelFast<Tkernel, Mkernel, Mkernel>& kernel,
    const uint8_t* input,
    size_t ncols,
    size_t nrows,
    size_t channels,
    uint8_t* output
)
{
    std::unique_ptr<float[]> new_pixel { new float[channels] };

    for (size_t y = 0; y < nrows; ++y) {
        for (size_t x = 0; x < ncols; ++x) {
            std::fill_n(new_pixel.get(), channels, static_cast<float>(0.0f));

            for (int ky = 0; ky < Mkernel; ++ky) {
                for (int kx = 0; kx < Nkernel; ++kx) {
                    auto kc = kernel.w[ky][kx];

                    int input_x = static_cast<int>(x - Nkernel / 2 + kx);
                    int input_y = static_cast<int>(y - Mkernel / 2 + ky);

                    // Adjust input coordinate if kernel is overhanging the input image's side/top.
                    if (input_x < 0)
                        input_x = 0;
                    else if (input_x >= ncols)
                        input_x = ncols - 1;
                    if (input_y < 0)
                        input_y = 0;
                    else if (input_y >= nrows)
                        input_y = nrows - 1;

                    auto input_pixel = &input[input_y*ncols*channels + input_x*channels];

                    for (int i = 0; i < channels; ++i) {
                        new_pixel[i] += kc * (*(input_pixel + i));
                    }
                }
            }

            for (int i = 0; i < channels; ++i) {
                output[y*ncols*channels + x*channels + i] = static_cast<uint8_t>(new_pixel[i]);
            }
        }
    }
}


// Performs a convolution on the input data using the supplied filter kernel.
//
// [parameters]
// kernel - The prefilled kernel.
// input - The input data to process.
// ncols - Number of cols of the input data (e.g. the image's width)
// nrows - Number of rows of the input data (e.g. the image's height)
// channels - Number of channels in the input data (e.g. 3 for RGB images).
// output - Output of the processed data. May be provided to the function uninitialized.
//
// [notes]
//  - This convolution implementation may not be mathematically pure since it does not involve
//    flipping of the kernel's matrix.
void convolute(
    const IKernel<float>& kernel,
    const uint8_t* input,
    size_t ncols,
    size_t nrows,
    size_t channels,
    uint8_t* output
);


// Performs convolution over a specified range of rows in an image, known as the work area.
//
// [parameters]
// kernel - The prefilled kernel.
// input - The input data to process.
// ncols - Number of cols of the input data (e.g. the image's width)
// nrows - Number of rows of the input data (e.g. the image's height)
// channels - Number of channels in the input data (e.g. 3 for RGB images).
// output - Output of the processed data. May be provided to the function uninitialized.
// start_row - The row which processing should start.
// end_row - One past the row which should be processed.
//
// [notes]
//  - This convolution implementation may not be mathematically pure since it does not involve
//    flipping of the kernel's matrix.
template<typename Tkernel, size_t Mkernel, size_t Nkernel>
void convolute_work_area(
    const KernelFast<Tkernel, Mkernel, Nkernel>& kernel,
    const uint8_t* input,
    size_t ncols,
    size_t nrows,
    size_t channels,
    uint8_t* output,
    size_t start_row,
    size_t end_row
)
{
    std::unique_ptr<float[]> new_pixel { new float[channels] };

    for (size_t y = start_row; y < end_row; ++y) {
        for (size_t x = 0; x < ncols; ++x) {
            std::fill_n(new_pixel.get(), channels, static_cast<float>(0.0f));

            for (int ky = 0; ky < Mkernel; ++ky) {
                for (int kx = 0; kx < Nkernel; ++kx) {
                    auto kc = kernel.w[ky][kx];

                    int input_x = static_cast<int>(x - Nkernel / 2 + kx);
                    int input_y = static_cast<int>(y - Mkernel / 2 + ky);

                    // Adjust input coordinate if kernel is overhanging the input image's side/top.
                    if (input_x < 0)
                        input_x = 0;
                    else if (input_x >= ncols)
                        input_x = ncols - 1;
                    if (input_y < 0)
                        input_y = 0;
                    else if (input_y >= nrows)
                        input_y = nrows - 1;

                    auto input_pixel = &input[input_y*ncols*channels + input_x*channels];

                    for (int i = 0; i < channels; ++i) {
                        new_pixel[i] += kc * (*(input_pixel + i));
                    }
                }
            }

            for (int i = 0; i < channels; ++i) {
                output[y*ncols*channels + x*channels + i] = static_cast<uint8_t>(new_pixel[i]);
            }
        }
    }
}


// Performs convolution over a specified range of rows in an image, known as the work area.
//
// [parameters]
// kernel - The prefilled kernel.
// input - The input data to process.
// ncols - Number of cols of the input data (e.g. the image's width)
// nrows - Number of rows of the input data (e.g. the image's height)
// channels - Number of channels in the input data (e.g. 3 for RGB images).
// output - Output of the processed data. May be provided to the function uninitialized.
// start_row - The row which processing should start.
// end_row - One past the row which should be processed.
//
// [notes]
//  - This convolution implementation may not be mathematically pure since it does not involve
//    flipping of the kernel's matrix.
template<typename Tkernel>
void convolute_work_area(
    const IKernel<Tkernel>& kernel,
    const uint8_t* input,
    size_t ncols,
    size_t nrows,
    size_t channels,
    uint8_t* output,
    size_t start_row,
    size_t end_row
)
{
    std::unique_ptr<float[]> new_pixel { new float[channels] };

    for (size_t y = start_row; y < end_row; ++y) {
        for (size_t x = 0; x < ncols; ++x) {
            std::fill_n(new_pixel.get(), channels, static_cast<float>(0.0f));

            for (int ky = 0; ky < kernel.size_m(); ++ky) {
                for (int kx = 0; kx < kernel.size_n(); ++kx) {
                    auto kc = kernel.at(ky, kx);

                    int input_x = static_cast<int>(x - kernel.size_n() / 2 + kx);
                    int input_y = static_cast<int>(y - kernel.size_m() / 2 + ky);

                    // Adjust input coordinate if kernel is overhanging the input image's side/top.
                    if (input_x < 0)
                        input_x = 0;
                    else if (input_x >= ncols)
                        input_x = ncols - 1;
                    if (input_y < 0)
                        input_y = 0;
                    else if (input_y >= nrows)
                        input_y = nrows - 1;

                    auto input_pixel = &input[input_y*ncols*channels + input_x*channels];

                    for (int i = 0; i < channels; ++i) {
                        new_pixel[i] += kc * (*(input_pixel + i));
                    }
                }
            }

            for (int i = 0; i < channels; ++i) {
                output[y*ncols*channels + x*channels + i] = static_cast<uint8_t>(new_pixel[i]);
            }
        }
    }
}


// Performs threaded convolution.
template<typename Tkernel, size_t Mkernel, size_t Nkernel>
void convolute_threaded(
    size_t num_threads,
    const KernelFast<Tkernel, Mkernel, Nkernel>& kernel,
    const uint8_t* input,
    size_t ncols,
    size_t nrows,
    size_t channels,
    uint8_t* output
)
{
    std::vector<std::future<void>> funcs;
    for (size_t i = 0; i < num_threads; ++i) {
        funcs.push_back(
            std::move(std::async(
                convolute_work_area<Tkernel, Mkernel, Nkernel>,
                kernel,
                input,
                ncols,
                nrows,
                channels,
                output,
                nrows * i / num_threads,
                nrows * (i + 1) / num_threads
            )
        ));
    }

    for (auto& future : funcs) {
        future.get();
    }
}

// Performs threaded convolution.
template<typename Tkernel>
void convolute_threaded(
    size_t num_threads,
    const IKernel<Tkernel>& kernel,
    const uint8_t* input,
    size_t ncols,
    size_t nrows,
    size_t channels,
    uint8_t* output
)
{
    throw std::exception();

    std::vector<std::future<void>> funcs;
    for (size_t i = 0; i < num_threads; ++i) {
        // NOTE: I have been unable to get the commented out section below to compile.
        /*funcs.push_back(
            std::move(std::async(
                convolute_work_area<Tkernel>,
                kernel,
                input,
                ncols,
                nrows,
                channels,
                output,
                nrows * i / num_threads,
                nrows * (i + 1) / num_threads
            )
        ));*/
    }

    for (auto& future : funcs) {
        future.get();
    }
}


}
}

#endif //LTS_FILTER_OPERATIONS_H
