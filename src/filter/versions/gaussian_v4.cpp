#include "filter/gaussian.h"
#include "filter/versions/gaussian_v4.h"
#include "filter/operations.h"

namespace LTS {
namespace filter {
namespace versions {


GaussianKernel_v4::GaussianKernel_v4()
{
    load_gaussian(kernel);
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
