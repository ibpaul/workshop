#include "filter/gaussian.h"

#include <stdexcept>

using namespace std;

namespace LTS {
namespace filter {

void load_gaussian(KernelBase<float>& kernel)
{
	assert(kernel.size_n() == 3 && kernel.size_m() == 3);

    kernel.at(0, 0) = 1 / 11.f;
    kernel.at(0, 1) = 1 / 11.f;
    kernel.at(0, 2) = 1 / 11.f;
    kernel.at(1, 0) = 1 / 11.f;
    kernel.at(1, 1) = 3 / 11.f;
    kernel.at(1, 2) = 1 / 11.f;
    kernel.at(2, 0) = 1 / 11.f;
    kernel.at(2, 1) = 1 / 11.f;
    kernel.at(2, 2) = 1 / 11.f;
}

}
}
