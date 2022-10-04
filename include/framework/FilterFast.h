// Wraps a KernelFast object and associated process method.

#ifndef LTS_FRAMEWORK_FILTERFAST_H
#define LTS_FRAMEWORK_FILTERFAST_H

#include <memory>
#include "framework/IFilter.h"
#include "filter/Kernel.h"

namespace LTS {
namespace framework {

template<typename T, size_t M, size_t N>
class FilterFast : public IFilter
{
public:
    using ProcessFunction = void (*)(
        const filter::KernelFast<T, M, N>&, const uint8_t* input,
        size_t, size_t, size_t, uint8_t*);

    FilterFast(std::unique_ptr<filter::KernelFast<T,M,N>> kernel, ProcessFunction process)
        : _kernel(move(kernel)),
          _process(process)
    { }

    void process(uint8_t *data, size_t height, size_t width, size_t channels, uint8_t *output) override
    {
        _process(*_kernel, data, height, width, channels, output);
    }

private:
    std::unique_ptr<filter::KernelFast<T, M, N>> _kernel;
    ProcessFunction _process;
};

}
}

#endif //LTS_FRAMEWORK_FILTERFAST_H
