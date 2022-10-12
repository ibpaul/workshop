#include "filter/operations.h"
#include <memory>

using namespace std;


namespace lts {
namespace filter {


void convolute(
    const Eigen::MatrixXf& kernel,
    const uint8_t* input,
    size_t ncols,
    size_t nrows,
    size_t channels,
    uint8_t* output)
{
    unique_ptr<float[]> new_pixel { new float[channels] };

    for (size_t y = 0; y < nrows; ++y) {
        for (size_t x = 0; x < ncols; ++x) {
            fill_n(new_pixel.get(), channels, static_cast<float>(0.0f));

            for (int ky = 0; ky < kernel.rows(); ++ky) {
                for (int kx = 0; kx < kernel.cols(); ++kx) {
                    auto kc = kernel(ky, kx);

                    int input_x = static_cast<int>(x - kernel.cols() / 2 + kx);
                    int input_y = static_cast<int>(y - kernel.rows() / 2 + ky);

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


}
}
