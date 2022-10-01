#include "filter/Kernel.h"

namespace LTS {
namespace filter {


Kernel_2d::Kernel_2d(size_t ncols, size_t nrows)
    : _ncols(ncols),
      _nrows(nrows),
      _own(true)
      #if !OPTIMIZE_3
      ,
      _weights(new float[ncols*nrows])
      #endif
{ }


Kernel_2d::~Kernel_2d()
{
    #if !OPTIMIZE_3
    if (_own)
        delete[] _weights;
    #endif
}


}
}
