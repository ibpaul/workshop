#include "filter/gaussian.h"
#include <cassert>


using namespace std;


namespace lts {
namespace filter {


size_t point_to_normal(size_t v, size_t midpoint)
{
    return (v - midpoint) * 3 / midpoint;
}


}
}
