#include "framework/FilterFactory.h"
#include <utility>
#include <stdexcept>
#include <queue>
#include "framework/FilterFast.h"
#include "framework/Filter.h"
#include "filter/Kernel.h"
#include "filter/gaussian.h"
#include "filter/operations.h"
#include "util/string.h"

using namespace std;
using lts::filter::KernelFast;
using lts::filter::Kernel;
using lts::filter::IKernel;
using lts::filter::load_gaussian;
using lts::filter::convolute;
using lts::util::starts_with;
using lts::util::split;

namespace lts {
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
        auto size_m = static_cast<size_t>(stoi(parts_q.front()));
        parts_q.pop();

        if (parts_q.empty()) {
            throw invalid_argument("only 2-dimensional kernels supported at the time");
        }
        auto size_n = static_cast<size_t>(stoi(parts_q.front()));
        parts_q.pop();

        bool use_no_fast = false;
        if (!parts_q.empty()) {
            auto p = parts_q.front();
            if (p == "nofast") {
                use_no_fast = true;
                parts_q.pop();
            }
        }

        // See if we can make a FilterFast.
        if (size_m == size_n && !use_no_fast) {
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
        unique_ptr<IKernel<float>> kernel {new Kernel<float>{size_m, size_n}};
        load_gaussian(*kernel);

        return unique_ptr<IFilter>(new Filter<float>(
            std::move(kernel),
            &convolute
        ));
    } else {
        throw invalid_argument("cannot process filter specification of '" + spec + "'");
    }
}

}
}
