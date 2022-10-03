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

    auto midpoint_x = kernel.size_n() / 2;
    auto midpoint_y = kernel.size_m() / 2;

    for (size_t y = midpoint_y; y < kernel.size_m(); ++y) {
        auto cur_norm_y = util::normal_pdf(_point_to_normal(y, midpoint_y));

        for (size_t x = midpoint_x; x < kernel.size_n(); ++x) {
            auto cur_norm_x = util::normal_pdf(_point_to_normal(x, midpoint_x));
            auto val = cur_norm_x * cur_norm_y;
            kernel.at(x, y) = val;
        }

        // We only compute the kernel for positive values. Copy the computed values into the mirror quadrant.
        // HACK: This relies on knowing the internal workings of Kernel.
        auto row_start = &kernel.at(0, y);
        reverse_copy(row_start + midpoint_x - 1, row_start + kernel.size_n(), row_start);
    }

    // We have computed the kernel for one quadrant, copied the values to another quadrant. Let's copy the values
    // into the other half of the kernel now.
    // HACK: This relies on knowing the internal workings of Kernel.
    for (size_t y = 0; y < midpoint_y; ++y) {
        auto row_start_src = &kernel.at(0, kernel.size_m() - y - 1);
        auto row_start_dest = &kernel.at(0, y);
        copy(row_start_src, row_start_src + kernel.size_n(), row_start_dest);
    }
}

}
}
