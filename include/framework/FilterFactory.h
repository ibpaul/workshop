// Creates runnable objects composed of a kernel and process method.

#ifndef LTS_FRAMEWORK_FILTERFACTORY_H
#define LTS_FRAMEWORK_FILTERFACTORY_H

#include <memory>
#include <string>
#include "framework/IFilter.h"

namespace lts {
namespace framework {


class FilterFactory
{
public:
    std::unique_ptr<IFilter> create(const std::string& spec);
    std::unique_ptr<IFilter> create(const std::string& spec, int num_threads);
};


}
}

#endif //LTS_FRAMEWORK_FILTERFACTORY_H
