// Wraps a Kernel object and associated process method.

#ifndef LTS_FRAMEWORK_FILTER_H
#define LTS_FRAMEWORK_FILTER_H

#include <memory>
#include "framework/IFilter.h"
#include "math/Matrix.h"

namespace lts {
namespace framework {


template<typename T>
class Filter : public IFilter
{
public:
    using ProcessFunction = void (*)(
        const math::IMatrix<T>&, const uint8_t*,
        size_t, size_t, size_t, uint8_t*);

    Filter(std::unique_ptr<math::IMatrix<T>> kernel, ProcessFunction process)
        : _kernel(move(kernel)),
          _process(process)
    { }

    void process(uint8_t *data, size_t width, size_t height, size_t channels, uint8_t *output) override
    {
        _process(*_kernel, data, width, height, channels, output);
    }

private:
    std::unique_ptr<math::IMatrix<T>> _kernel;
    ProcessFunction _process;
};


}
}

#endif //LTS_FRAMEWORK_FILTER_H
