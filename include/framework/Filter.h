// Wraps a Kernel object and associated process method.

#ifndef LTS_FRAMEWORK_FILTER_H
#define LTS_FRAMEWORK_FILTER_H

#include <memory>
#include <Eigen/Dense>
#include "framework/IFilter.h"


namespace lts {
namespace framework {


template<template <typename, int, int...> class TMatrix, typename T, int M, int N>
class Filter : public IFilter
{
public:
    using ProcessFunction = void (*)(
        const TMatrix<T, M, N>&, const uint8_t* input,
        size_t, size_t, size_t, uint8_t*);

    Filter(std::unique_ptr<TMatrix<T,M,N>> kernel, ProcessFunction process)
        : _kernel(move(kernel)),
          _process(process)
    { }

    void process(uint8_t *data, size_t width, size_t height, size_t channels, uint8_t *output) override
    {
        _process(*_kernel, data, width, height, channels, output);
    }

private:
    std::unique_ptr<TMatrix<T, M, N>> _kernel;
    ProcessFunction _process;
};


}
}

#endif //LTS_FRAMEWORK_FILTER_H
