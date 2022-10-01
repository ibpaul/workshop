#include "filter/versions/gaussian_v2.h"


// [OPTIMIZE NOTES]
//  - Only enable either OPTIMIZE_1 or OPTIMIZE_2. Do not enable both!

#define OPTIMIZE_1 1
// OPTIMIZE_1 changes who the kernel weights are accessed in the filter's for loops.
// Instead of accessing them like below each time in the for loop...
//
//     weights[y*num_cols + x]
//
// ...we access them like below...
//
//     *weights_ptr++
//
// This optimization relies on the nested for loops accessing the kernel weights sequentially
// and thus avoids the multiplication during each loop.
//
// This does appear to give a performance increase but is still slower than the implementation
// in Gaussian_v1 where the elements are stored in a multidimensional array and accessed like
// the code below...
//
//     weights[y][x]
//

#define OPTIMIZE_2 0
// OPTIMIZE_2 is not expected to provide any noticeable performance increase.
//
// It eliminates a variable from the inner loops and instead dereferences the pointer access
// as implemented in OPTIMIZE_1.


namespace LTS {
namespace filter {
namespace versions {


GaussianKernel_v2::GaussianKernel_v2()
    : norm_factor{11.0f},
      size{3},
      kernel{3, 3}
{
    kernel._weights[0] = 1;
    kernel._weights[1] = 1;
    kernel._weights[2] = 1;
    kernel._weights[3] = 1;
    kernel._weights[4] = 3;
    kernel._weights[5] = 1;
    kernel._weights[6] = 1;
    kernel._weights[7] = 1;
    kernel._weights[8] = 1;
}


void GaussianKernel_v2::process(const uint8_t* input, size_t width, size_t height, uint8_t* output, int channels)
{
    std::unique_ptr<float[]> new_pixel { new float[channels] };

    for (size_t x = 0; x < width; ++x) {
        for (size_t y = 0; y < height; ++y) {
            std::fill_n(new_pixel.get(), channels, static_cast<float>(0.0f));

            #if OPTIMIZE_1 || OPTIMIZE_2
            // This optimization avoids a multiplication in accessing the kernel weights as long
            // as the kernel weights are processed a row at a time in the for loops.
            //
            // This still doesn't seem as fast as when the kernel weights were stored and accessed
            // in from a multidimensional array in the for loops.
            auto kc_p = kernel._weights;
            #endif

            for (int ky = 0; ky < size; ++ky) {
                for (int kx = 0; kx < size; ++kx) {
                    #if OPTIMIZE_1
                    auto kc = *kc_p++;
                    #elif OPTIMIZE_2
                    // Do nothing.
                    #else
                    auto kc = kernel._weights[ky*kernel._ncols + kx];
                    #endif

                    int input_x = static_cast<int>(x - size / 2 + kx);
                    int input_y = static_cast<int>(y - size / 2 + ky);

                    // Adjust input coordinate if kernel is overhanging the input image's side/top.
                    if (input_x < 0)
                        input_x = 0;
                    else if (input_x >= width)
                        input_x = width - 1;
                    if (input_y < 0)
                        input_y = 0;
                    else if (input_y >= height)
                        input_y = height - 1;

                    auto input_pixel = &input[input_y*width*channels + input_x*channels];

                    for (int i = 0; i < channels; ++i) {
                        #if OPTIMIZE_2
                        new_pixel[i] += (*kc_p) * (*(input_pixel + i));
                        #else
                        new_pixel[i] += kc * (*(input_pixel + i));
                        #endif
                    }
                    #if OPTIMIZE_2
                    kc_p++;
                    #endif
                }
            }

            for (int i = 0; i < channels; ++i) {
                output[y*width*channels + x*channels + i] = static_cast<uint8_t>(new_pixel[i] / norm_factor);
            }
        }
    }
}


}
}
}
