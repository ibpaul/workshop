#include "filter/Kernel.h"

namespace LTS {
namespace filter {


Kernel_2d::Kernel_2d(size_t ncols, size_t nrows)
    : _ncols(ncols),
      _nrows(nrows),
      _own(true),
      _weights(new float[ncols*nrows])
{ }


Kernel_2d::~Kernel_2d()
{
    if (_own)
        delete[] _weights;
}


}
}
