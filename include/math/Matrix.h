// Kernel functionality for signal processing.

#ifndef LTS_MATH_MATRIX_H
#define LTS_MATH_MATRIX_H

#include <cstddef>
#include <cstdint>
#include <memory>
#include <array>
#ifdef LTS_EIGEN_MATRIX
    #include "Eigen/Dense"
#endif
#include "optimize_flags.h"

namespace lts {
namespace math {

#ifndef LTS_EIGEN_MATRIX
// Abstract base class for all matrices. All our generalized kernel processing functions work on this interface.
template<typename T>
class IMatrix {

public:
    virtual size_t size_m() const = 0;      // Number of rows in the kernel.
    virtual size_t size_n() const = 0;      // Number of columns in the kernel
    virtual T& at(size_t m, size_t n) = 0;  // Access and set element at index (m, n).
    virtual const T& at(size_t m, size_t n) const = 0;
    virtual ~IMatrix() { }

    virtual IMatrix& operator*=(T scalar)
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
class MatrixFast : public IMatrix<T> {
public:
    #ifdef LTS_KERNEL_FAST_NATIVE_MULTIDIM_ARRAY
    T w[M][N];  // Weights.
    #else
    std::array<std::array<T, N>, M> w;  // Weights.
    #endif

    size_t size_m() const override { return M; }
    size_t size_n() const override { return N; }
    T& at(size_t m, size_t n) override { return w[m][n]; }
    const T& at(size_t m, size_t n) const override { return w[m][n]; }
};


// General matrix.
template<typename T>
class Matrix : public IMatrix<T> {
public:
    Matrix(size_t m, size_t n)
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


/*template<typename T>
class MatrixEigen : public IMatrix<T> {
public:
    MatrixEigen(size_t m, size_t n)
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
};*/
#endif


}
}

#endif //LTS_MATH_MATRIX_H
