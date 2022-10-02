// Kernel functionality for signal processing.

#ifndef LTS_FILTER_KERNEL_H
#define LTS_FILTER_KERNEL_H

#include <cstddef>
#include <cstdint>
#include "optimize_flags.h"

namespace LTS {
namespace filter {


// Abstract base class for all kernels. All our generalized kernel processing functions work on this interface.
template<typename T>
class IKernel {

public:
    virtual size_t size_n() = 0;
    virtual size_t size_m() = 0;
    virtual T& at(size_t x, size_t y) = 0;
};


// Templated kernel. This is currently the fastest implementation of a kernel available (based on test runs through our
// convolute() method. To make sure you have this performance gain, make sure you call the convolute() method with this
// type and not as it's base IKernel type.
//
// [notes]
//  - The performance gains are a result of:
//      a) the kernel weights are accessed by the multidimensional array instead of computing pointer offsets.
//      b) the templated convolute<>() method uses the N and M parameters to specify the kernel for loops and the
//         compiler is able to perform further optimizations on these loops.
template<typename T, size_t N, size_t M>
class KernelFast : public IKernel<T> {
public:
    T w[N][M];  // Weights.

    size_t size_n() override { return N; }
    size_t size_m() override { return M; }
    T& at(size_t x, size_t y) override { return w[y][x]; }
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
