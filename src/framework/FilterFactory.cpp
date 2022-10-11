#include "framework/FilterFactory.h"
#include <utility>
#include <stdexcept>
#include <queue>
#include <map>
#include "framework/FilterFast.h"
#include "framework/Filter.h"


// TODO: Remove.
#include "math/Matrix.h"


#include "filter/gaussian.h"
#include "filter/operations.h"
#include "util/string.h"

using namespace std;
#ifndef LTS_EIGEN_MATRIX
using lts::math::MatrixFast;
using lts::math::Matrix;
using lts::math::IMatrix;
using lts::math::MatrixEigen;
#endif
using lts::filter::load_gaussian;
using lts::filter::convolute;
using lts::filter::convolute_threaded;
using lts::util::starts_with;
using lts::util::split;

namespace lts {
namespace framework {


#ifdef LTS_EIGEN_MATRIX
// HACK: Would like to specify the matrices size as defined by the Eigen library.
template<int S>
#else
template<size_t S>
#endif
std::unique_ptr<IFilter> make_fast_filter(int num_threads)
{
    #ifdef LTS_EIGEN_MATRIX
    auto kernel = make_unique<Eigen::Matrix<float, S, S>>();
    #else
    auto kernel = make_unique<MatrixFast<float, S, S>>();
    #endif

    load_gaussian(*kernel);

    if (num_threads == 0) {
        #ifdef LTS_EIGEN_MATRIX
        return unique_ptr<IFilter>(new FilterFast<float, S, S>(
            std::move(kernel),
            &convolute<float, S, S>
        ));
        #else
        return unique_ptr<IFilter>(new FilterFast<float, S, S>(
            std::move(kernel),
            &convolute<float, S, S>
        ));
        #endif
    } else {
        #ifdef LTS_EIGEN_MATRIX
        //throw runtime_error("not implemented");
        // TODO: Convert to Eigen matrix.
        auto func = [](const Eigen::Matrix<float, S, S>& k, const uint8_t* input, size_t width, size_t height, size_t channels, uint8_t* output) {
            convolute_threaded(5, k, input, width, height, channels, output);
        };
        #else
        auto func = [](const math::MatrixFast<float, S, S>& k, const uint8_t* input, size_t width, size_t height, size_t channels, uint8_t* output) {
            convolute_threaded(5, k, input, width, height, channels, output);
        };
        #endif

        #ifdef LTS_EIGEN_MATRIX
        // TODO: Convert to Eigen matrix.
        return unique_ptr<IFilter>(new FilterFast<float, S, S>(
            std::move(kernel),
            func
        ));
        #else
        return unique_ptr<IFilter>(new FilterFast<float, S, S>(
            std::move(kernel),
            func
        ));
        #endif
    }
}


map<string, bool> FilterFactory::process_use_flags(queue<string>& params)
{
    map<string, bool> use_flags {
        {"nofast", false},
        {"eigen", false}
    };

    while (!params.empty()) {
        auto p = params.front();
        params.pop();

        if (use_flags.find(p) == use_flags.end()) {
            throw runtime_error("unrecognized filter option '" + p + "'");
        }

        use_flags[p] = true;
    }

    return use_flags;
}


pair<size_t, size_t> FilterFactory::process_matrix_sizing(queue<string>& params, const string& spec)
{
    if (params.empty()) {
        throw invalid_argument("no kernel size specified in '" + spec + "'");
    }
    auto size_m = static_cast<size_t>(stoi(params.front()));
    params.pop();

    if (params.empty()) {
        throw invalid_argument("only 2-dimensional kernels supported at the time");
    }
    auto size_n = static_cast<size_t>(stoi(params.front()));
    params.pop();

    return make_pair(size_m, size_n);
}


std::unique_ptr<IFilter> FilterFactory::create(const std::string& spec, int num_threads)
{
    map<string, int> patterns {
        make_pair("gaussian", 0)
    };

    auto elements = lts::util::split(spec, {',', '{', '}'});

    queue<string, deque<string>> q {deque<string> {elements.begin(), elements.end()}};

    auto type_name = q.front();
    q.pop();

    if (patterns.find(type_name) == patterns.end()) {
        throw invalid_argument("cannot process filter specification of '" + spec + "'");
    }

    auto size = process_matrix_sizing(q, spec);

    auto flags = process_use_flags(q);

    if (flags["eigen"]) {
        #ifdef LTS_EIGEN_MATRIX
        throw runtime_error("deprecated");
        #else
        if (flags["nofast"]) {
            throw runtime_error("options 'eigen' and 'nofast' can not be used together");
        }

        unique_ptr<IMatrix<float>> kernel {new MatrixEigen<float>{size.first, size.second}};
        load_gaussian(*kernel);

        return unique_ptr<IFilter>(new Filter<float>(
            std::move(kernel),
            &convolute
        ));
        #endif
    } else if (size.first == size.second && !flags["nofast"]) {
        // We can make a FilterFast.
        if (size.first == 3)
            return make_fast_filter<3>(num_threads);
        if (size.first == 5)
            return make_fast_filter<5>(num_threads);
        if (size.first == 7)
            return make_fast_filter<7>(num_threads);
        if (size.first == 9)
            return make_fast_filter<9>(num_threads);
        if (size.first == 11)
            return make_fast_filter<11>(num_threads);
    }

    if (num_threads > 0) {
        // We don't have multi-threading enabled for generic kernels yet.
        throw runtime_error("cannot run multi-threaded for provided spec");
    }

    // Fallback on making a normal Filter.
    #ifdef LTS_EIGEN_MATRIX
    auto kernel = make_unique<Eigen::MatrixXf>(size.first, size.second);
    //unique_ptr<Eigen::MatrixXf> kernel {new Matrix<float>{size.first, size.second}};
    #else
    unique_ptr<IMatrix<float>> kernel {new Matrix<float>{size.first, size.second}};
    #endif

    load_gaussian(*kernel);

    return unique_ptr<IFilter>(new Filter<float>(
        std::move(kernel),
        &convolute
    ));
}


unique_ptr<IFilter> FilterFactory::create(const string& spec)
{
    return FilterFactory::create(spec, 0);
}

}
}
