// Wraps a KernelFast object and associated process method.

#ifndef LTS_FRAMEWORK_FILTERFAST_H
#define LTS_FRAMEWORK_FILTERFAST_H

#include <memory>
#include "framework/IFilter.h"

#ifdef LTS_EIGEN_MATRIX
    #include "math/SimpleMatrix.h"
    #include <Eigen/Dense>
#else
    #include "math/Matrix.h"
#endif

namespace lts {
namespace framework {


#ifdef LTS_EIGEN_MATRIX

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

#endif


template<typename T, size_t M, size_t N>
class FilterFast : public IFilter
{
public:
    #ifdef LTS_EIGEN_MATRIX
    using ProcessFunction = void (*)(
        const Eigen::Matrix<T, M, N>&, const uint8_t* input,
        size_t, size_t, size_t, uint8_t*);
    #else
    using ProcessFunction = void (*)(
        const math::MatrixFast<T, M, N>&, const uint8_t* input,
        size_t, size_t, size_t, uint8_t*);
    #endif

    #ifdef LTS_EIGEN_MATRIX
    FilterFast(std::unique_ptr<Eigen::Matrix<T,M,N>> kernel, ProcessFunction process)
    #else
    FilterFast(std::unique_ptr<math::MatrixFast<T,M,N>> kernel, ProcessFunction process)
    #endif
        : _kernel(move(kernel)),
          _process(process)
    { }

    void process(uint8_t *data, size_t width, size_t height, size_t channels, uint8_t *output) override
    {
        _process(*_kernel, data, width, height, channels, output);
    }

private:
    #ifdef LTS_EIGEN_MATRIX
std::unique_ptr<Eigen::Matrix<T, M, N>> _kernel;
    #else
    std::unique_ptr<math::MatrixFast<T, M, N>> _kernel;
    #endif
    ProcessFunction _process;
};

}
}

#endif //LTS_FRAMEWORK_FILTERFAST_H
