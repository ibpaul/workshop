// Gaussian (blur) filter for images.

#ifndef LTS_FILTER_GAUSSIAN_H
#define LTS_FILTER_GAUSSIAN_H

#include "filter/Kernel.h"

namespace lts {
namespace filter {

void load_gaussian(IKernel<float>& kernel);

}
}

#endif //LTS_FILTER_GAUSSIAN_H
