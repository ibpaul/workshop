// Wraps a KernelFast object and associated process method.

#ifndef LTS_FRAMEWORK_FILTERFAST_H
#define LTS_FRAMEWORK_FILTERFAST_H

#include <memory>
#include <Eigen/Dense>
#include "framework/IFilter.h"
#include "math/SimpleMatrix.h"


namespace lts {
namespace framework {


template<typename T, size_t M, size_t N>
class FilterSimple : public IFilter
{
public:
    using ProcessFunction = void (*)(
        const math::SimpleMatrix<T, M, N>&, const uint8_t* input,
        size_t, size_t, size_t, uint8_t*);

    FilterSimple(std::unique_ptr<math::SimpleMatrix<T,M,N>> kernel, ProcessFunction process)
        : _kernel(move(kernel)),
          _process(process)
    { }

    void process(uint8_t *data, size_t width, size_t height, size_t channels, uint8_t *output) override
    {
        _process(*_kernel, data, width, height, channels, output);
    }

private:
    std::unique_ptr<math::SimpleMatrix<T, M, N>> _kernel;
    ProcessFunction _process;
};


template<typename T, size_t M, size_t N>
class FilterFast : public IFilter
{
public:
    using ProcessFunction = void (*)(
        const Eigen::Matrix<T, M, N>&, const uint8_t* input,
        size_t, size_t, size_t, uint8_t*);

    FilterFast(std::unique_ptr<Eigen::Matrix<T,M,N>> kernel, ProcessFunction process)
        : _kernel(move(kernel)),
          _process(process)
    { }

    void process(uint8_t *data, size_t width, size_t height, size_t channels, uint8_t *output) override
    {
        _process(*_kernel, data, width, height, channels, output);
    }

private:
    std::unique_ptr<Eigen::Matrix<T, M, N>> _kernel;
    ProcessFunction _process;
};

}
}

#endif //LTS_FRAMEWORK_FILTERFAST_H
