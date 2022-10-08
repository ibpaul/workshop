// Interface for an object that holds a kernel and a process object.

#ifndef LTS_FRAMEWORK_IFILTER_H
#define LTS_FRAMEWORK_IFILTER_H

#include <cstdint>

namespace lts {
namespace framework {

class IFilter {
public:
    virtual void process(uint8_t* data, size_t height, size_t width, size_t channels, uint8_t* output) = 0;
    virtual ~IFilter() = default;
};

}
}

#endif //LTS_FRAMEWORK_IFILTER_H
