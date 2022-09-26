#include "gaussian.h"


int test_func()
{
    return 37;
}

namespace LTS {
namespace filters {


GaussianKernel::GaussianKernel() : norm_factor{11.0f}, size{3} //: _kernel(new char[3][3])
{
    //_kernel = new char[3][3];
    kernel[0][0] = 1;
    kernel[0][1] = 1;
    kernel[0][2] = 1;
    kernel[1][0] = 1;
    kernel[1][1] = 3;
    kernel[1][2] = 1;
    kernel[2][0] = 1;
    kernel[2][1] = 1;
    kernel[2][2] = 1;
}


void GaussianKernel::process(const uint8_t* input, size_t width, size_t height, uint8_t* output)
{
    for (size_t x = 0; x < width; ++x) {
        for (size_t y = 0; y < height; ++y) {
            float new_pixel{};

            for (int ky = 0; ky < size; ++ky) {
                for (int kx = 0; kx < size; ++kx) {
                    //auto kc = kernel[ky*width + kx];
                    auto kc = kernel[ky][kx];

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

                    auto input_pixel = input[input_y*width + input_x];

                    new_pixel += kc * input_pixel;
                }
            }

            output[y*width + x] = static_cast<uint8_t>(new_pixel / norm_factor);
        }
    }
}


}
}
