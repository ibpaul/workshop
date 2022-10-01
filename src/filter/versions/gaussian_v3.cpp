#include "filter/versions/gaussian_v3.h"
#include "filter/operations.h"

namespace LTS {
namespace filter {
namespace versions {


GaussianKernel_v3::GaussianKernel_v3()
    : norm_factor{11.0f},
      size{3},
      kernel{3, 3}
{
    #if OPTIMIZE_3
    kernel._weights[0][0] = 1;
    kernel._weights[0][1] = 1;
    kernel._weights[0][2] = 1;
    kernel._weights[1][0] = 1;
    kernel._weights[1][1] = 3;
    kernel._weights[1][2] = 1;
    kernel._weights[2][0] = 1;
    kernel._weights[2][1] = 1;
    kernel._weights[2][2] = 1;
    #else
    kernel._weights[0] = 1;
    kernel._weights[1] = 1;
    kernel._weights[2] = 1;
    kernel._weights[3] = 1;
    kernel._weights[4] = 3;
    kernel._weights[5] = 1;
    kernel._weights[6] = 1;
    kernel._weights[7] = 1;
    kernel._weights[8] = 1;
    #endif
}


void GaussianKernel_v3::process(const uint8_t* input, size_t width, size_t height, uint8_t* output, int channels)
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
