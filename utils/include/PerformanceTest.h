// Manager class for performing timing analysis.

#ifndef LTS_UTILS_PERFORMANCETEST_H
#define LTS_UTILS_PERFORMANCETEST_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

namespace LTS {
namespace utils {


class PerformanceTest
{
public:
    using TestFunc = void (*)();

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
    // under_test - Function which will have its performance tested.
    //
    // [DEV_NOTES]
    // The test function was templated to allow passing capturing lambdas. This probably uses std::function to pass
    // as a function argument which is characteristically bloated and may degrade true timing testing but is assumed
    // to be insignificant while working on computationally intensive algorithms. Watch out for time testing on smaller
    // and simpler algorithms.
    //void test(TestFunc test_func);
    template<typename Callable>
    void test(Callable test_func)
    {
        print_test_start();

        for (auto test_num = 0; test_num < _iterations; ++test_num) {
            auto begin = std::chrono::high_resolution_clock::now();

            test_func();

            auto end = std::chrono::high_resolution_clock::now();
            auto diff = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000.0;

            _durations[test_num] = diff;
        }

        print_test_end();
        print_test_statistics();
        save_report_file();
    }

    // Sets the stream to write display information to during the test.
    //
    // [parameters]
    // s - The stream which the testing system will write status/results information to during test.
    void set_display_stream(std::ostream& s);

private:
    void print_test_start();
    void print_test_end();
    void print_test_statistics();
    void save_report_file();

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
