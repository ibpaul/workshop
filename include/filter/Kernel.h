// Kernel functionality for signal processing.

#ifndef LTS_FILTER_KERNEL_H
#define LTS_FILTER_KERNEL_H

#include <cstddef>
#include <cstdint>
#include <memory>
#include "Eigen/Dense"
#include "optimize_flags.h"

namespace lts {
namespace filter {


// Abstract base class for all kernels. All our generalized kernel processing functions work on this interface.
template<typename T>
class IKernel {

public:
    virtual size_t size_m() const = 0;      // Number of rows in the kernel.
    virtual size_t size_n() const = 0;      // Number of columns in the kernel
    virtual T& at(size_t m, size_t n) = 0;  // Access and set element at index (m, n).
    virtual const T& at(size_t m, size_t n) const = 0;
    virtual ~IKernel() { }

    virtual IKernel& operator*=(T scalar)
    {
        for (size_t m = 0; m < size_m(); ++m) {
            for (size_t n = 0; n < size_n(); ++n) {
                at(m, n) *= scalar;
            }
        }

        return *this;
    }
};


// Templated kernel. This is currently the fastest implementation of a kernel available (based on test runs through our
// convolute() method. To make sure you have this performance gain, make sure you call the convolute() method with this
// type and not as it's base IKernel type.
//
// [notes]
//  - The performance gains are a result of:
//      a) the kernel weights are accessed by the multidimensional array instead of computing pointer offsets.
//      b) the templated convolute<>() method uses the M and N parameters to specify the kernel for loops and the
//         compiler is able to perform further optimizations on these loops.
template<typename T, size_t M, size_t N>
class KernelFast : public IKernel<T> {
public:
    #ifdef LTS_KERNEL_FAST_ARRAY_MEMBER
    std::array<T, M*N> w;
    #else
    T w[M][N];  // Weights.
    #endif

    size_t size_m() const override { return M; }
    size_t size_n() const override { return N; }

    #ifdef LTS_KERNEL_FAST_ARRAY_MEMBER
    T& at(size_t m, size_t n) override { return w[m * N + n]; }
    const T& at(size_t m, size_t n) const override { return w[m * N + n]; }
    #else
    T& at(size_t m, size_t n) override { return w[m][n]; }
    const T& at(size_t m, size_t n) const override { return w[m][n]; }
    #endif
};


// General kernel.
template<typename T>
class Kernel : public IKernel<T> {
public:
    Kernel(size_t m, size_t n)
        : w {new T[m*n]},
          _m {m},
          _n {n}
    { }

    size_t size_m() const override { return _m; }
    size_t size_n() const override { return _n; }
    T& at(size_t m, size_t n) override { return w[m * _n + n]; }
    const T& at(size_t m, size_t n) const override { return w[m * _n + n]; }

#if !OPTIMIZE_5
private:
#endif
    std::unique_ptr<T[]> w;
    size_t _m;
    size_t _n;
};


template<typename T>
class KernelEigen : public IKernel<T> {
public:
    KernelEigen(size_t m, size_t n)
        : w(m, n)
    { }

    size_t size_m() const override { return w.rows(); }
    size_t size_n() const override { return w.cols(); }
    T& at(size_t m, size_t n) override { return w(m, n); }
    const T& at(size_t m, size_t n) const override { return w(m, n); }

#if !OPTIMIZE_5
private:
#endif
    Eigen::MatrixXf w;
};



}
}

#endif //LTS_FILTER_KERNEL_H
