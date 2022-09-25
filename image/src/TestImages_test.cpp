#include <gtest/gtest.h>
#include "TestImages.h"


TEST(IMAGE_TEST, Generate10x10LinearTestImage) {
    constexpr int width = 10;
    constexpr int height = 10;

    auto image = LTS::image::vertical_lines(width, height);

    uint8_t expected[] = {
        0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
        0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
        0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
        0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
        0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
        0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
        0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
        0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
        0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
        0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
    };

    for (int i = 0; i < width*height; ++i)
        EXPECT_EQ(expected[i], image[i]);
}

TEST(IMAGE_TEST, Generate3x3LinearTestImage) {
    constexpr size_t width = 5;
    constexpr size_t height = 3;

    auto image = LTS::image::vertical_lines(width, height);

    uint8_t expected[] = {
        0, 255, 0, 255, 0,
        0, 255, 0, 255, 0,
        0, 255, 0, 255, 0,
    };

    for (int i = 0; i < width*height; ++i)
        EXPECT_EQ(expected[i], image[i]);
}
