// Gaussian (blur) filter for images.
#ifndef LTS_FILTERS_VERSIONS_GAUSSIAN_V0_H
#define LTS_FILTERS_VERSIONS_GAUSSIAN_V0_H

#include <memory>
#include "filter/ImageKernel.h"


namespace LTS {
namespace filter {
namespace versions {

// Gaussian (blur) filter for images.
//
// [NOTES]
// Can not handle alpha channels.
//
// [DEV_NOTES]
//  - Would like to make this general instead of for just 2-D operations (e.g. 1-D and 3-D options).
//  - Would like to make a base class called Kernel.
//  - Make into template for different parameter types.
//  - Only makes a simple 3x3 kernel for now.
class GaussianKernel_v0 : public ImageKernel {

public:
    GaussianKernel_v0();

    // Runs the Gaussian filter over the input image and places result into output.
    void process(const uint8_t* input, size_t width, size_t height, uint8_t* output, int channels);

    ~GaussianKernel_v0() {};
private:
    //std::unique_ptr<char[3][3]> _kernel;
    float kernel[3][3];
    float norm_factor;
    size_t size;
};

}
}
}

#endif // LTS_FILTERS_VERSIONS_GAUSSIAN_V0_H

