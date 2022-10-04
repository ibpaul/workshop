// Wraps a Kernel object and associated process method.

#ifndef LTS_FRAMEWORK_FILTER_H
#define LTS_FRAMEWORK_FILTER_H

#include <memory>
#include "framework/IFilter.h"
#include "filter/Kernel.h"

namespace LTS {
namespace framework {


template<typename T>
class Filter : public IFilter
{
public:
    using ProcessFunction = void (*)(
        const filter::IKernel<T>&, const uint8_t*,
        size_t, size_t, size_t, uint8_t*);

    Filter(std::unique_ptr<filter::IKernel<T>> kernel, ProcessFunction process)
        : _kernel(move(kernel)),
          _process(process)
    { }

    void process(uint8_t *data, size_t height, size_t width, size_t channels, uint8_t *output) override
    {
        _process(*_kernel, data, height, width, channels, output);
    }

private:
    std::unique_ptr<filter::IKernel<T>> _kernel;
    ProcessFunction _process;
};


}
}

#endif //LTS_FRAMEWORK_FILTER_H
