#include "filter/gaussian.h"
#include <cassert>
#include <algorithm>
#include "util/statistics.h"

using namespace std;

namespace LTS {
namespace filter {


size_t _point_to_normal(size_t v, size_t midpoint)
{
    return (v - midpoint) * 3 / midpoint;
}


void load_gaussian(IKernel<float>& kernel)
{
    // Our copy methods won't work on this size, and it doesn't make much sense anyway for a kernel this size.
    assert(kernel.size_m() > 2 && kernel.size_n() > 2);

    // We only allow odd sizes for m and n.
    assert((kernel.size_m() % 2) && (kernel.size_n() % 2));

    auto midpoint_n = kernel.size_n() / 2;
    auto midpoint_m = kernel.size_m() / 2;

    for (size_t m = midpoint_m; m < kernel.size_m(); ++m) {
        auto cur_norm_m = util::normal_pdf(_point_to_normal(m, midpoint_m));

        for (size_t n = midpoint_n; n < kernel.size_n(); ++n) {
            auto cur_norm_n = util::normal_pdf(_point_to_normal(n, midpoint_n));
            auto val = cur_norm_n * cur_norm_m;
            kernel.at(m, n) = val;
        }

        // We only compute the kernel for positive values. Copy the computed values into the mirror quadrant.
        // HACK: This relies on knowing the internal workings of Kernel.
        auto row_start = &kernel.at(m, 0);
        reverse_copy(row_start + midpoint_n - 1, row_start + kernel.size_n(), row_start);
    }

    // We have computed the kernel for one quadrant, copied the values to another quadrant. Let's copy the values
    // into the other half of the kernel now.
    // HACK: This relies on knowing the internal workings of Kernel.
    for (size_t m = 0; m < midpoint_m; ++m) {
        auto row_start_src = &kernel.at(kernel.size_m() - m - 1, 0);
        auto row_start_dest = &kernel.at(m, 0);
        copy(row_start_src, row_start_src + kernel.size_n(), row_start_dest);
    }

    // HACK: Adjustment to get the processed image at the same level of brightness.
//    kernel *= 3.0f;
}

}
}
