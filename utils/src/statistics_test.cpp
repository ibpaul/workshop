#include <gtest/gtest.h>
#include "statistics.h"


TEST(UTILS_TEST, StatisticsMean) {
    const std::vector<float> values {3.0, 4.0, 8.0 };

    auto result = LTS::utils::mean(values);

    EXPECT_EQ(5.0, result);
}

TEST(UTILS_TEST, StatisticsStandardDeviation) {
    const std::vector<float> values {10, 12, 23, 23, 16, 23, 21, 16};

    auto result = LTS::utils::standard_deviation(values);

    EXPECT_NEAR(5.2372293656638, result, 0.0001);
}