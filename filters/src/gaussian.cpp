#include "gaussian.h"


int test_func()
{
    return 37;
}

namespace LTS {
namespace filters {

GaussianKernel::GaussianKernel() //: _kernel(new char[3][3])
{
    //_kernel = new char[3][3];
    _kernel[0][0] = 1;
    _kernel[0][1] = 1;
    _kernel[0][1] = 1;
    _kernel[1][0] = 1;
    _kernel[1][1] = 3;
    _kernel[1][2] = 1;
    _kernel[2][0] = 1;
    _kernel[2][1] = 1;
    _kernel[2][2] = 1;
}

}
}
