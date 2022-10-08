// Common filtering operations.

#ifndef LTS_FILTER_OPERATIONS_H
#define LTS_FILTER_OPERATIONS_H

#include <cstddef>
#include <memory>
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


}
}

#endif //LTS_FILTER_OPERATIONS_H
