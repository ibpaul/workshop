#include "framework/FilterFactory.h"
#include <utility>
#include "framework/FilterFast.h"
#include "filter/Kernel.h"
#include "filter/gaussian.h"
#include "filter/operations.h"

using namespace std;
using LTS::filter::KernelFast;
using LTS::filter::load_gaussian;
using LTS::filter::convolute;

namespace LTS {
namespace framework {

unique_ptr<IFilter> FilterFactory::create(const string& spec)
{
    // HACK: No processing of the spec yet. Just testing out gluing the framework together.
    auto kernel = make_unique<KernelFast<float, 3, 3>>();
    load_gaussian(*kernel);

    return unique_ptr<IFilter>(new FilterFast<float, 3, 3>(
        std::move(kernel),
        &convolute<float, 3, 3>
    ));
}

}
}
