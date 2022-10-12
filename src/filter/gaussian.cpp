#include "filter/gaussian.h"
#include <cassert>
#include "util/statistics.h"

using namespace std;
using Eigen::Matrix2f;


namespace lts {
namespace filter {


size_t _point_to_normal(size_t v, size_t midpoint)
{
    return (v - midpoint) * 3 / midpoint;
}


void load_gaussian(Eigen::MatrixXf& kernel)
{
    // Our copy methods won't work on this size, and it doesn't make much sense anyway for a kernel this size.
    assert(kernel.rows() > 2 && kernel.cols() > 2);

    // We only allow odd sizes for m and n.
    assert((kernel.rows() % 2) && (kernel.cols() % 2));

    auto midpoint_n = kernel.cols() / 2;
    auto midpoint_m = kernel.rows() / 2;

    for (size_t m = midpoint_m; m < kernel.rows(); ++m) {
        auto cur_norm_m = util::normal_pdf(_point_to_normal(m, midpoint_m));

        for (size_t n = midpoint_n; n < kernel.cols(); ++n) {
            auto cur_norm_n = util::normal_pdf(_point_to_normal(n, midpoint_n));
            auto val = cur_norm_n * cur_norm_m;
            kernel(m, n) = val;
        }

        // We only compute the kernel for positive values. Copy the computed values into the mirror quadrant.
        for (size_t pos = 0; pos < midpoint_n; ++pos)
            kernel(m, pos) = kernel(m, kernel.cols() - pos - 1);
    }

    // We have computed the kernel for one quadrant, copied the values to another quadrant. Let's copy the values
    // into the other half of the kernel now.
    for (size_t row = 0; row < midpoint_m; ++row) {
        for (size_t col = 0; col < kernel.cols(); ++col) {
            kernel(row, col) = kernel(kernel.rows() - row - 1, col);
        }
    }

    // HACK: Adjustment to get the processed image at the same level of brightness.
//    kernel *= 3.0f;
}


}
}
