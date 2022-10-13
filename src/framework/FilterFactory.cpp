#include "framework/FilterFactory.h"
#include <utility>
#include <stdexcept>
#include <queue>
#include <map>
#include "framework/Filter.h"
#include "math/SimpleMatrix.h"
#include "filter/gaussian.h"
#include "filter/operations.h"
#include "util/string.h"


using namespace std;
using lts::math::SimpleMatrix;
using lts::filter::load_gaussian;
using lts::filter::convolute;
using lts::filter::convolute_threaded;
using lts::util::starts_with;
using lts::util::split;


namespace lts {
namespace framework {


template<template <typename, int, int...> class TMatrix, int S>
std::unique_ptr<IFilter> FilterFactory::make_static_filter(int num_threads)
{
    auto kernel = make_unique<TMatrix<float, S, S>>();

    load_gaussian(*kernel);

    if (num_threads == 0) {
        return unique_ptr<IFilter>(new Filter<TMatrix, float, S, S>(
            std::move(kernel),
            &convolute
        ));
    } else {
        auto func = [](const TMatrix<float, S, S>& k, const uint8_t* input, size_t width, size_t height, size_t channels, uint8_t* output) {
            convolute_threaded(5, k, input, width, height, channels, output);
        };

        return unique_ptr<IFilter>(new Filter<TMatrix, float, S, S>(
            std::move(kernel),
            func
        ));
    }
}


map<string, bool> FilterFactory::process_use_flags(queue<string>& params)
{
    map<string, bool> use_flags {
        {"nofast", false},
        {"simple", false}
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

    if (flags["simple"]) {
        if (size.first != size.second)
            throw invalid_argument("matrix sizes must be the same for option 'simple'");

        if (size.first == 3)
            return make_static_filter<SimpleMatrix, 3>(num_threads);
        if (size.first == 5)
            return make_static_filter<SimpleMatrix, 5>(num_threads);
        if (size.first == 7)
            return make_static_filter<SimpleMatrix, 7>(num_threads);
        if (size.first == 9)
            return make_static_filter<SimpleMatrix, 9>(num_threads);
        if (size.first == 11)
            return make_static_filter<SimpleMatrix, 11>(num_threads);
    } else if (size.first == size.second && !flags["nofast"]) {
        if (size.first == 3)
            return make_static_filter<Eigen::Matrix, 3>(num_threads);
        if (size.first == 5)
            return make_static_filter<Eigen::Matrix, 5>(num_threads);
        if (size.first == 7)
            return make_static_filter<Eigen::Matrix, 7>(num_threads);
        if (size.first == 9)
            return make_static_filter<Eigen::Matrix, 9>(num_threads);
        if (size.first == 11)
            return make_static_filter<Eigen::Matrix, 11>(num_threads);
    }

    // Fallback on making a normal Filter.
    auto kernel = make_unique<Eigen::MatrixXf>(size.first, size.second);
    load_gaussian(*kernel);

    if (num_threads > 0) {
        // We don't have multi-threading enabled for generic kernels yet.
        //throw runtime_error("cannot run multi-threaded for provided spec");

        auto func = [](const Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>& k, const uint8_t* input, size_t width, size_t height, size_t channels, uint8_t* output) {
            convolute_threaded(5, k, input, width, height, channels, output);
        };

        return unique_ptr<IFilter>(new Filter<Eigen::Matrix, float, Eigen::Dynamic, Eigen::Dynamic>(
            std::move(kernel),
            func
        ));
    }

    return unique_ptr<IFilter>(new Filter<Eigen::Matrix, float, Eigen::Dynamic, Eigen::Dynamic>(
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
