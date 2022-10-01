// Kernel functionality for signal processing.

#ifndef LTS_FILTER_KERNEL_H
#define LTS_FILTER_KERNEL_H

#include <cstddef>
#include <cstdint>
#include "optimize_flags.h"

namespace LTS {
namespace filter {


template<typename T>
class KernelBase {

public:
    virtual size_t size_n() = 0;
    virtual size_t size_m() = 0;
    virtual T& at(size_t x, size_t y) = 0;
};


// Templated 2-dimensional kernel.
template<typename T, size_t N, size_t M>
class Kernel : public KernelBase<T> {
public:
    T w[N][M];  // Weights.

    size_t size_n() override { return N; }
    size_t size_m() override { return M; }
    T& at(size_t x, size_t y) override { return w[y][x]; }
};


// A 2-dimensional kernel.
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


//public:
    // Perform the convolution over the input data.
//    void convolute(size_t width, size_t height, size_t channels, const uint8_t* input, uint8_t* output);
};

}
}

#endif //LTS_FILTER_KERNEL_H
