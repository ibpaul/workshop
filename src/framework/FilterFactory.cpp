#include "framework/FilterFactory.h"
#include <utility>
#include <stdexcept>
#include <queue>
#include "framework/FilterFast.h"
#include "filter/Kernel.h"
#include "filter/gaussian.h"
#include "filter/operations.h"
#include "util/string.h"

using namespace std;
using LTS::filter::KernelFast;
using LTS::filter::load_gaussian;
using LTS::filter::convolute;
using LTS::util::starts_with;
using LTS::util::split;

namespace LTS {
namespace framework {


template<size_t S>
std::unique_ptr<IFilter> make_fast_filter()
{
    auto kernel = make_unique<KernelFast<float, S, S>>();
    load_gaussian(*kernel);

    return unique_ptr<IFilter>(new FilterFast<float, S, S>(
        std::move(kernel),
        &convolute<float, S, S>
    ));
}


unique_ptr<IFilter> FilterFactory::create(const string& spec)
{
    if (starts_with(spec, "gaussian")) {
        auto parts = split(spec, {',', '{', '}'});
        queue<string, deque<string>> parts_q {deque<string> {parts.begin(), parts.end()}};

        // We are not processing specific filter versions/types at the moment.
        parts_q.pop();

        if (parts_q.empty()) {
            throw invalid_argument("no kernel size specified in '" + spec + "'");
        }
        auto size_m = stoi(parts_q.front());
        parts_q.pop();

        if (parts_q.empty()) {
            throw invalid_argument("only 2-dimensional kernels supported at the time");
        }
        auto size_n = stoi(parts_q.front());
        parts_q.pop();

        // See if we can make a FilterFast.
        if (size_m == size_n) {
            if (size_m == 3)
                return make_fast_filter<3>();
            if (size_m == 5)
                return make_fast_filter<5>();
            if (size_m == 7)
                return make_fast_filter<7>();
            if (size_m == 9)
                return make_fast_filter<9>();
            if (size_m == 11)
                return make_fast_filter<11>();
        }

        // Fallback on making a normal Filter.

        throw invalid_argument("not implemented");


    } else {
        throw invalid_argument("cannot process filter specification of '" + spec + "'");
    }
}

}
}
