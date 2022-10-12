// Creates runnable objects composed of a kernel and process method.

#ifndef LTS_FRAMEWORK_FILTERFACTORY_H
#define LTS_FRAMEWORK_FILTERFACTORY_H

#include <memory>
#include <string>
#include <map>
#include <queue>
#include "framework/IFilter.h"

namespace lts {
namespace framework {


class FilterFactory
{
public:
    static std::unique_ptr<IFilter> create(const std::string& spec);
    static std::unique_ptr<IFilter> create(const std::string& spec, int num_threads);

private:
    static std::map<std::string, bool> process_use_flags(std::queue<std::string>& params);
    static std::pair<size_t, size_t> process_matrix_sizing(std::queue<std::string>& params, const std::string& spec);

    template<template <typename, int, int...> class TMatrix, int S>
    static std::unique_ptr<IFilter> make_static_filter(int num_threads);
};


}
}

#endif //LTS_FRAMEWORK_FILTERFACTORY_H
