#include "PerformanceTest.h"
#include <utility>
#include <chrono>
#include "File.h"
#include "statistics.h"

namespace LTS {
namespace utils {


PerformanceTest::PerformanceTest(size_t iterations, std::string report_file, bool display)
    : _iterations(iterations),
      _reportFile(std::move(report_file)),
      _display(display),
      _displayStream(&std::cout),
      _durations(iterations)
{ }

//void PerformanceTest::test(TestFunc test_func)
/*{
    print_test_start();

    for (auto test_num = 0; test_num < _iterations; ++test_num) {
        auto begin = std::chrono::high_resolution_clock::now();

        test_func();

        auto end = std::chrono::high_resolution_clock::now();
        auto diff = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000.0;

        _durations[test_num] = diff;
    }

    print_test_end();
    save_report_file();
}*/

void PerformanceTest::set_display_stream(std::ostream& s)
{
    _displayStream = &s;
}

void PerformanceTest::print_test_start()
{
    if (_display) {
        *_displayStream << "[Test Start]" << std::endl;
    }
}

void PerformanceTest::print_test_end()
{
    if (_display) {
        *_displayStream << "[Test End]" << std::endl;
    }
}

void PerformanceTest::print_test_statistics()
{
    if (_display) {
        *_displayStream << "[Test Results]" << std::endl;
        *_displayStream << "mean time (ms): " << LTS::utils::mean(_durations) << std::endl;
        *_displayStream << "jitter (std dev): " << LTS::utils::standard_deviation(_durations) << std::endl;
    }
}

void PerformanceTest::save_report_file()
{
    if (_reportFile.empty())
        return;

    LTS::utils::File timeReportFile(_reportFile, "w");
    fprintf(timeReportFile(), "IndividualRunTimes\n");

    for (auto& d : _durations)
        fprintf(timeReportFile(), "%f ms\n", d);
}


}
}
