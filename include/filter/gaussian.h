// Gaussian (blur) filter for images.

#ifndef LTS_FILTER_GAUSSIAN_H
#define LTS_FILTER_GAUSSIAN_H

#include "math/Matrix.h"

namespace lts {
namespace filter {

void load_gaussian(math::IMatrix<float>& kernel);

}
}

#endif //LTS_FILTER_GAUSSIAN_H
