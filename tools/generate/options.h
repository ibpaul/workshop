// Program options and command-line processing.

#ifndef LTS_TOOLS_GENERATE_OPTIONS_H
#define LTS_TOOLS_GENERATE_OPTIONS_H

#include <string>


struct Options {
    enum class Operation {
        ImageToCpp
    };

    Operation operation;
    int num_params_provided {0};
    std::string string_param_0;
    std::string string_param_1;
};

// Process and determine all command-line options provided. Will call printer error and call exit() for invalid
// parameters provided by user and for the --help flag.
Options process_all_options(int argc, char* argv[]);


#endif //LTS_TOOLS_GENERATE_OPTIONS_H
