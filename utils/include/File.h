// Wrapper around FILE adding safe and automatic resource release.

#ifndef LTS_UTILS_FILE_H
#define LTS_UTILS_FILE_H

#include <cstdio>
#include <stdexcept>

namespace LTS {
namespace utils {


class File {
public:
    // Opens a file.
    //
    // [parameters]
    // filename - Name of file to open.
    // access - Access flags as used for fopen().
    File(const char* filename, const char* access)
        : f{fopen(filename, access)}
    {
        if (f == nullptr) throw std::runtime_error("unable to open file");
    }

    // Opens a file.
    //
    // [parameters]
    // filename - Name of file to open.
    // access - Access flags as used for fopen().
    File(const std::string& filename, const char* access)
        : File(filename.c_str(), access)
    { }

    // Transfer ownership of an open file handle.
    //
    // [parameters]
    // file - A handle to an open file.
    explicit File(FILE* file)
        : f{file}
    {
        if (f == nullptr) throw std::runtime_error("nullptr provided");
    }

    // TODO: Add move and copy operations.

    ~File() { fclose(f); }

    // Provides access to the underlying file handle.
    FILE* operator()() { return f; }

private:
    FILE* f;
};


}
}

#endif //LTS_UTILS_FILE_H
