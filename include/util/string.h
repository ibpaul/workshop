// String utilities.

#ifndef LTS_UTIL_STRING_H
#define LTS_UTIL_STRING_H

#include <vector>
#include <string>

namespace lts {
namespace util {

// Splits a string up using the supplied deliminator.
std::vector<std::string> split(const std::string& str, char delim);

// Splits a string up using the supplied deliminators.
std::vector<std::string> split(const std::string& str, const std::vector<char>& delims);

// Checks if a provided string starts with the provided check string.
bool starts_with(const std::string& str, const std::string& check);

}
}

#endif //LTS_UTIL_STRING_H
