#include "util/statistics.h"

namespace LTS {
namespace util {


float normal_pdf(float x, float sigma, float mu)
{
    // coefficient
    const float co = 1.0f / (sigma * sqrtf(2.0f * static_cast<float>(M_PI)));

    // exponent
    float ex = - (1.0f / 2.0f) * powf(((x - mu) / sigma), 2.0f);

    return co * powf(M_E, ex);
}


}
}