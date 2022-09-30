#include "util/string.h"
#include <sstream>

using namespace std;

namespace LTS {
namespace util {

vector<string> split(const string& str, char delim)
{
    stringstream str_stream(str);
    vector<string> segments;
    string seg;

    while (getline(str_stream, seg, delim)) {
        segments.push_back(seg);
    }

    return segments;
}


vector<string> split(const string& str, const vector<char>& delims)
{
    vector<string> segments;
    string delims_str;

    for (char c : delims)
        delims_str += c;

    size_t prev {0};
    size_t pos;

    while ((pos = str.find_first_of(delims_str, prev)) != string::npos) {
        if (pos > prev)
            segments.push_back(str.substr(prev, pos-prev));
        prev = pos + 1;
    }
    if (prev < str.length())
        segments.push_back(str.substr(prev, string::npos));

    return segments;
}


bool starts_with(const std::string& str, const std::string& check)
{
    return str.rfind(check, 0) == 0;
}


}
}
