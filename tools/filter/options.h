// Program options and command-line processing.

#ifndef LTS_WORKSHOP_TOOLS_FILTER_OPTIONS_H
#define LTS_WORKSHOP_TOOLS_FILTER_OPTIONS_H

#include <string>


struct Options {
    std::string input_file;
    std::string output_file;
    std::string report_file;
    bool test;
};

// Process and determine all command-line options provided. Will call printer error and call exit() for invalid
// parameters provided by user and for the --help flag.
Options process_all_options(int argc, char* argv[]);


#endif //LTS_WORKSHOP_TOOLS_FILTER_OPTIONS_H
