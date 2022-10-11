#include "filter/operations.h"
#include <memory>

using namespace std;
#ifndef LTS_EIGEN_MATRIX
using lts::math::IMatrix;
#endif

namespace lts {
namespace filter {


void convolute(
    #ifdef LTS_EIGEN_MATRIX
    const Eigen::MatrixXf& kernel,
    #else
    const IMatrix<float>& kernel,
    #endif
    const uint8_t* input,
    size_t ncols,
    size_t nrows,
    size_t channels,
    uint8_t* output)
{
    #if OPTIMIZE_5
    const Kernel<float>& kernel = *dynamic_cast<const Kernel<float>*>(&ikernel);
    #endif

    unique_ptr<float[]> new_pixel { new float[channels] };

    for (size_t y = 0; y < nrows; ++y) {
        for (size_t x = 0; x < ncols; ++x) {
            fill_n(new_pixel.get(), channels, static_cast<float>(0.0f));

            #if OPTIMIZE_1 || OPTIMIZE_2
            // This optimization avoids a multiplication in accessing the kernel weights as long
            // as the kernel weights are processed a row at a time in the for loops.
            //
            // This still doesn't seem as fast as when the kernel weights were stored and accessed
            // in from a multidimensional array in the for loops.
            auto kc_p = kernel._weights;
            #endif

            #if OPTIMIZE_4
            for (int ky = 0; ky < 3; ++ky) {
            for (int kx = 0; kx < 3; ++kx) {
            #elif OPTIMIZE_5
            for (int ky = 0; ky < kernel._m; ++ky) {
                for (int kx = 0; kx < kernel._n; ++kx) {
            #else

            #ifdef LTS_EIGEN_MATRIX
            for (int ky = 0; ky < kernel.rows(); ++ky) {
                for (int kx = 0; kx < kernel.cols(); ++kx) {
            #else
            for (int ky = 0; ky < kernel.size_m(); ++ky) {
                for (int kx = 0; kx < kernel.size_n(); ++kx) {
            #endif

            #endif
                    #if OPTIMIZE_1
                    auto kc = *kc_p++;
                    #elif OPTIMIZE_2
                    // Do nothing.
                    #elif OPTIMIZE_3
                    auto kc = kernel._weights[ky][kx];
                    #elif OPTIMIZE_5
                    auto kc = kernel.w[ky * kernel._n + kx];
                    #else
                    //auto kc = kernel._weights[ky*kernel._ncols + kx];
                    #ifdef LTS_EIGEN_MATRIX
                    auto kc = kernel(ky, kx);
                    #else
                    auto kc = kernel.at(ky, kx);
                    #endif

                    #endif

                    #if OPTIMIZE_4
                    int input_x = static_cast<int>(x - 3 / 2 + kx);
                    int input_y = static_cast<int>(y - 3 / 2 + ky);
                    #elif OPTIMIZE_5
                    int input_x = static_cast<int>(x - kernel._n / 2 + kx);
                    int input_y = static_cast<int>(y - kernel._m / 2 + ky);
                    #else

                    #ifdef LTS_EIGEN_MATRIX
                    int input_x = static_cast<int>(x - kernel.cols() / 2 + kx);
                    int input_y = static_cast<int>(y - kernel.rows() / 2 + ky);
                    #else
                    int input_x = static_cast<int>(x - kernel.size_n() / 2 + kx);
                    int input_y = static_cast<int>(y - kernel.size_m() / 2 + ky);
                    #endif

                    #endif

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
                output[y*ncols*channels + x*channels + i] = static_cast<uint8_t>(new_pixel[i]);
            }
        }
    }
}


}
}
