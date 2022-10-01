#include "filter/versions/gaussian_v4.h"
#include "filter/operations.h"

namespace LTS {
namespace filter {
namespace versions {


GaussianKernel_v4::GaussianKernel_v4()
    : norm_factor{11.0f},
      size{3}
{
    kernel.w[0][0] = 1;
    kernel.w[0][1] = 1;
    kernel.w[0][2] = 1;
    kernel.w[1][0] = 1;
    kernel.w[1][1] = 3;
    kernel.w[1][2] = 1;
    kernel.w[2][0] = 1;
    kernel.w[2][1] = 1;
    kernel.w[2][2] = 1;
}


void GaussianKernel_v4::process(const uint8_t* input, size_t width, size_t height, uint8_t* output, int channels)
{
    convolute(
        kernel,
        input,
        width,
        height,
        channels,
        output
    );
}


}
}
}
