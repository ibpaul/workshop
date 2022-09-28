#include "util/PerformanceTest.h"
#include <utility>
#include <chrono>
#include "util/File.h"
#include "util/statistics.h"

namespace LTS {
namespace util {


PerformanceTest::PerformanceTest(size_t iterations, std::string report_file, bool display)
    : _iterations(iterations),
      _reportFile(std::move(report_file)),
      _display(display),
      _displayStream(&std::cout),
      _durations(iterations)
{ }

void PerformanceTest::test(std::function<void()> test_func)
{
    print_test_start();

    auto begin_test = std::chrono::high_resolution_clock::now();

    for (auto test_num = 0; test_num < _iterations; ++test_num) {
        auto begin = std::chrono::high_resolution_clock::now();

        test_func();

        auto end = std::chrono::high_resolution_clock::now();
        auto diff = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000.0;

        _durations[test_num] = diff;
    }

    auto end_test = std::chrono::high_resolution_clock::now();
    auto diff_test = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end_test - begin_test).count()) / 1000.0;

    print_test_end();
    print_test_statistics(diff_test);
    save_report_file();
}

void PerformanceTest::test_threaded(std::vector<std::function<void()>> test_funcs)
{
    print_test_start();

    auto begin_test = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> tasks;
    std::vector<std::unique_ptr<TestHelper>> helpers;

    for (auto& tf : test_funcs) {
        auto th = std::make_unique<TestHelper>(_iterations, tf);

        // use emplace_back???
        tasks.push_back(std::thread(std::ref(*th)));

        helpers.push_back(std::move(th));
    }

    for (auto& t : tasks) {
        t.join();
    }

    _durations.resize(0);
    for (auto& th : helpers) {
        _durations.insert(_durations.end(), th->_durations.begin(), th->_durations.end());
    }

    auto end_test = std::chrono::high_resolution_clock::now();
    auto diff_test = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end_test - begin_test).count()) / 1000.0;

    print_test_end();
    print_test_statistics(diff_test);
    save_report_file();
}

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

void PerformanceTest::print_test_statistics(double total_test_time_ms)
{
    if (_display) {
        *_displayStream <<
            "[Test Results]" << std::endl <<
            "total test time (ms): " << total_test_time_ms << std::endl <<
            "mean time (ms): " << LTS::util::mean(_durations) << std::endl <<
            "jitter (std dev): " << LTS::util::standard_deviation(_durations) << std::endl;
    }
}

void PerformanceTest::save_report_file()
{
    if (_reportFile.empty())
        return;

    LTS::util::File timeReportFile(_reportFile, "w");
    fprintf(timeReportFile(), "IndividualRunTimes\n");

    for (auto& d : _durations)
        fprintf(timeReportFile(), "%f ms\n", d);
}

PerformanceTest::TestHelper::TestHelper(size_t iterations, std::function<void()> test_func)
    : _iterations(iterations),
      _test_func(test_func),
      _durations(iterations)
{ }

void PerformanceTest::TestHelper::operator()() {
    for (auto test_num = 0; test_num < _iterations; ++test_num) {
        auto begin = std::chrono::high_resolution_clock::now();

        _test_func();

        auto end = std::chrono::high_resolution_clock::now();
        auto diff = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000.0;

        _durations[test_num] = diff;
    }
}


}
}
