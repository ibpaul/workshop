// Small collection of statistical functions.

#ifndef LTS_UTILS_STATISTICS_H
#define LTS_UTILS_STATISTICS_H

#include <numeric>
#include <cmath>

namespace LTS {
namespace util {

// Computes the mean for a collection of values.
//
// [parameters]
// list - Container holding the values.
//
// [return]
// The computed mean of the provided values.
template<typename Container>
typename Container::value_type mean(Container vals)
{
    return std::accumulate(vals.begin(), vals.end(), static_cast<typename Container::value_type>(0)) / vals.size();
}


// Computes the standard deviation for the provided values.
//
// [parameters]
// list - Container holding the values.
template<typename Container>
typename Container::value_type standard_deviation(Container vals)
{
    auto m = mean(vals);

    auto sum = 0.0;
    for (auto& x : vals)
        sum += pow(x - m, 2);

    return sqrt(sum / (vals.size() - 1));
}


float normal_pdf(float x, float sigma = 1.0f, float mu = 0.0f);

}
}

#endif //LTS_UTILS_STATISTICS_H
