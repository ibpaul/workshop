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

}
}
