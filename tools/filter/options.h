// Program options and command-line processing.

#ifndef LTS_WORKSHOP_TOOLS_FILTER_OPTIONS_H
#define LTS_WORKSHOP_TOOLS_FILTER_OPTIONS_H

#include <string>
#include "config.h"


struct Options {
    std::string input;          // File or test pattern specification.
    std::string output_file;
    std::string report_file;
    bool test;
    int num_test_cycles {1};
    int num_test_threads {1};
    #if USE_FACTORY
    std::string filter_spec;
    #else
    std::string filter;
    int num_filter_params_provided {0};
    int filter_param_0_int {0};
    int filter_param_1_int {0};
    #endif
};

// Process and determine all command-line options provided. Will call printer error and call exit() for invalid
// parameters provided by user and for the --help flag.
Options process_all_options(int argc, char* argv[]);


#endif //LTS_WORKSHOP_TOOLS_FILTER_OPTIONS_H
