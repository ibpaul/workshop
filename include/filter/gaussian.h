// Gaussian (blur) filter for images.

#ifndef LTS_FILTER_GAUSSIAN_H
#define LTS_FILTER_GAUSSIAN_H

#include "versions/gaussian_v4.h"

namespace LTS {
namespace filter {

using GaussianKernel = versions::GaussianKernel_v4;

void load_gaussian(IKernel<float>& kernel);

}
}

#endif //LTS_FILTER_GAUSSIAN_H
