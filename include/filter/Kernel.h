// Kernel functionality for signal processing.

#ifndef LTS_FILTER_KERNEL_H
#define LTS_FILTER_KERNEL_H

#include <cstddef>
#include <cstdint>
#include <memory>
#include "optimize_flags.h"

namespace LTS {
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
    T w[M][N];  // Weights.

    size_t size_m() const override { return M; }
    size_t size_n() const override { return N; }
    T& at(size_t m, size_t n) override { return w[m][n]; }
    const T& at(size_t m, size_t n) const override { return w[m][n]; }
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

private:
    std::unique_ptr<T[]> w;
    size_t _m;
    size_t _n;
};


// A 2-dimensional kernel.
//
// NOTE: This is very old and will likely be removed.
struct Kernel_2d {

    bool _own;           // Flags if we own the memory.
    size_t _ncols;       // Number of columns.
    size_t _nrows;       // Number of rows.
    #if OPTIMIZE_3
    float _weights[3][3];
    #else
    float* _weights;     // Kernel's weights.
    #endif

    // Constructs a new, uninitialized kernel.
    Kernel_2d(size_t ncols, size_t nrows);

    // Deleting these for now. I haven't decided if we need them yet.
    Kernel_2d(const Kernel_2d& k) = delete;
    Kernel_2d& operator=(const Kernel_2d& k) = delete;


    ~Kernel_2d();
};

}
}

#endif //LTS_FILTER_KERNEL_H
