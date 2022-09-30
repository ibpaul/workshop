// Abstract base class for kernels meant for processing images.

#ifndef LTS_FILTER_IMAGEKERNEL_H
#define LTS_FILTER_IMAGEKERNEL_H

#include <cstddef>
#include <cstdint>

namespace LTS {
namespace filter {

class ImageKernel {
public:
    virtual void process(const uint8_t* input, size_t width, size_t height, uint8_t* output, int channels) = 0;
    virtual ~ImageKernel() {}
private:

};

}
}

#endif //LTS_FILTER_IMAGEKERNEL_H
