// Common filtering operations.

#ifndef LTS_FILTER_OPERATIONS_H
#define LTS_FILTER_OPERATIONS_H

#include <cstddef>
#include "filter/Kernel.h"

namespace LTS {
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
void convolute(
    const Kernel_2d& kernel,
    const uint8_t* input,
    size_t ncols,
    size_t nrows,
    size_t channels,
    uint8_t* output
);


}
}

#endif //LTS_FILTER_OPERATIONS_H
