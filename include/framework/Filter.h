// Wraps a Kernel object and associated process method.

#ifndef LTS_FRAMEWORK_FILTER_H
#define LTS_FRAMEWORK_FILTER_H

#include <memory>
#include <Eigen/Dense>
#include "framework/IFilter.h"


// TODO: Remove
//#include "math/Matrix.h"

namespace lts {
namespace framework {


template<typename T>
class Filter : public IFilter
{
public:
    #ifdef LTS_EIGEN_MATRIX
    using ProcessFunction = void (*)(
        const Eigen::MatrixX<T>&, const uint8_t*,
        size_t, size_t, size_t, uint8_t*);
    #else
    using ProcessFunction = void (*)(
        const math::IMatrix<T>&, const uint8_t*,
        size_t, size_t, size_t, uint8_t*);
    #endif

    #ifdef LTS_EIGEN_MATRIX
    //Filter(std::unique_ptr<Eigen::MatrixX<T>> kernel, ProcessFunction process)
    Filter(std::unique_ptr<Eigen::MatrixXf> kernel, ProcessFunction process)
    #else
    Filter(std::unique_ptr<math::IMatrix<T>> kernel, ProcessFunction process)
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
    std::unique_ptr<Eigen::MatrixXf> _kernel;
    //std::unique_ptr<Eigen::MatrixX<T>> _kernel;
    #else
    std::unique_ptr<math::IMatrix<T>> _kernel;
    #endif

    ProcessFunction _process;
};


}
}

#endif //LTS_FRAMEWORK_FILTER_H
