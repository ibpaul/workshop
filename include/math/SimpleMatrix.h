// Very simple 2-dimensional matrix.

#ifndef LTS_MATH_SIMPLEMATRIX_H
#define LTS_MATH_SIMPLEMATRIX_H

#include <array>

namespace lts {
namespace math {


template<typename T, int M_rows, int N_cols>
class SimpleMatrix {
public:
    static int cols() { return N_cols; }
    static int rows() { return M_rows; }

    T& operator()(int row, int col) { return elems[row][col]; }
    const T& operator()(int row, int col) const { return elems[row][col]; }

private:
    std::array<std::array<T, N_cols>, M_rows> elems;
};


}
}

#endif //LTS_MATH_SIMPLEMATRIX_H
