// Manager class for performing timing analysis.

#ifndef LTS_UTILS_PERFORMANCETEST_H
#define LTS_UTILS_PERFORMANCETEST_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <functional>

namespace lts {
namespace util {


class PerformanceTest
{
public:
    // Constructs a new performance test setup.
    //
    // [parameters]
    // iterations - Number of times to call the function to be tested.
    // report_file - File which will have consolidated test results written to. Set to empty to not write out results.
    // display - Display on-screen status and results.
    PerformanceTest(
        size_t iterations,
        std::string report_file = std::string(),
        bool display = true);

    // Performs the performance test.
    //
    // [parameters]
    // test_func - Function which will have its performance tested.
    //
    // [notes]
    // Using std::function as the parameter type so that our method can use capturing lambdas.
    void test(std::function<void()> test_func);

    // Performs a threaded performance test.
    //
    // [parameters]
    // test_funcs - Collection of functions to be run on separate threads. Caller's responsibility the individual
    //     functions provided do not share data incorrectly between the individual functions provided.
    //
    // [notes]
    //  - Each function will be called the number of times provided in 'iterations' when this class' constructor was
    //    called (e.g. 4 test funcs provided with 100 iterations -> 400 total function calls).
    void test_threaded(std::vector<std::function<void()>> test_funcs);

    // Sets the stream to write display information to during the test.
    //
    // [parameters]
    // s - The stream which the testing system will write status/results information to during test.
    void set_display_stream(std::ostream& s);

private:
    void print_test_start();
    void print_test_end();
    void print_test_statistics(double total_test_time_ms);
    void save_report_file();

    struct TestHelper {
        std::function<void()> _test_func;
        size_t _iterations;
        std::vector<float> _durations;

        TestHelper(size_t iterations, std::function<void()> test_func);
        void operator()();
    };

private:
    size_t _iterations;
    std::string _reportFile;
    bool _display;
    std::ostream* _displayStream;
    std::vector<float> _durations;
};

}
}

#endif //LTS_UTILS_PERFORMANCETEST_H
