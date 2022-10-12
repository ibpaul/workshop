// Gaussian (blur) filter for images.

#ifndef LTS_FILTER_GAUSSIAN_H
#define LTS_FILTER_GAUSSIAN_H


#include <Eigen/Dense>
#include "util/statistics.h"


namespace lts {
namespace filter {


size_t point_to_normal(size_t v, size_t midpoint);


template<typename TMatrix>
void load_gaussian(TMatrix& m)
{
    // Our copy methods won't work on this size, and it doesn't make much sense anyway for a kernel this size.
    assert(m.rows() > 2 && m.cols() > 2);

    // We only allow odd sizes for m and n.
    assert((m.rows() % 2) && (m.cols() % 2));

    auto midpoint_j = m.cols() / 2;
    auto midpoint_i = m.rows() / 2;

    for (size_t i = midpoint_i; i < m.rows(); ++i) {
        auto cur_norm_m = util::normal_pdf(point_to_normal(i, midpoint_i));

        for (size_t j = midpoint_j; j < m.cols(); ++j) {
            auto cur_norm_n = util::normal_pdf(point_to_normal(j, midpoint_j));
            auto val = cur_norm_n * cur_norm_m;
            m(i, j) = val;
        }

        // We only compute the kernel for positive values. Copy the computed values into the mirror quadrant.
        for (size_t pos = 0; pos < midpoint_j; ++pos)
            m(i, pos) = m(i, m.cols() - pos - 1);
    }

    // We have computed the kernel for one quadrant, copied the values to another quadrant. Let's copy the values
    // into the other half of the kernel now.
    for (size_t row = 0; row < midpoint_i; ++row) {
        for (size_t col = 0; col < m.cols(); ++col) {
            m(row, col) = m(m.rows() - row - 1, col);
        }
    }

    // HACK: Adjustment to get the processed image at the same level of brightness.
//    kernel *= 3.0f;
}


}
}

#endif //LTS_FILTER_GAUSSIAN_H
