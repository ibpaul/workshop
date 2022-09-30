// String utilities.

#ifndef LTS_UTIL_STRING_H
#define LTS_UTIL_STRING_H

#include <vector>
#include <string>

namespace LTS {
namespace util {

// Splits a string up using the supplied deliminator.
std::vector<std::string> split(const std::string& str, char delim);
std::vector<std::string> split(const std::string& str, const std::vector<char>& delims);

}
}

#endif //LTS_UTIL_STRING_H
