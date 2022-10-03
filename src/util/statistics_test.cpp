#include <gtest/gtest.h>
#include <utility>
#include "util/statistics.h"

using std::vector;
using std::pair;
using namespace LTS::util;


TEST(UTILS_TEST, StatisticsMean1) {
    const vector<float> values { 3.0, 4.0, 8.0 };

    auto result = mean(values);

    EXPECT_EQ(5.0, result);
}

TEST(UTILS_TEST, StatisticsMean2) {
    const vector<float> values {3.0, 4.0, 8.5 };

    auto result = mean(values);

    EXPECT_NEAR(5.16666651, result, 0.0001);
}

TEST(UTILS_TEST, StatisticsStandardDeviation) {
    const vector<float> values {10, 12, 23, 23, 16, 23, 21, 16};

    auto result = standard_deviation(values);

    EXPECT_NEAR(5.2372293656638, result, 0.0001);
}

TEST(UTILS_TEST, NormalPDF_1_0) {
    auto t1 = pair<float, float>(0.0f, 0.398942280);
    auto t2 = pair<float, float>(1.0f, 0.241970725);
    auto t3 = pair<float, float>(-3.0f, 0.00443185);

    auto r1 = normal_pdf(t1.first);
    auto r2 = normal_pdf(t2.first);
    auto r3 = normal_pdf(t3.first);

    EXPECT_NEAR(t1.second, r1, 0.0001);
    EXPECT_NEAR(t2.second, r2, 0.0001);
    EXPECT_NEAR(t3.second, r3, 0.0001);
}