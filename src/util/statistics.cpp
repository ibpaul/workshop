#include "util/statistics.h"

constexpr float pi_f = 3.14159265358979323846f;
constexpr float e_f = 2.718281828459045;

namespace LTS {
namespace util {


float normal_pdf(float x, float sigma, float mu)
{
    // coefficient
    const float co = 1.0f / (sigma * sqrtf(2.0f * static_cast<float>(pi_f)));

    // exponent
    float ex = - (1.0f / 2.0f) * powf(((x - mu) / sigma), 2.0f);

    return co * powf(e_f, ex);
}


}
}