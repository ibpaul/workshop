#include <gtest/gtest.h>
#include "TestImages.h"
#include "Gaussian.h"


TEST(GAUSSIAN_TEST, GaussianFilterOn10x10MonochromeVerticalLinesImage) {
    constexpr int width = 10;
    constexpr int height = 10;

    auto image = LTS::image::vertical_lines(width, height);
    uint8_t output[width*height]{};

    LTS::filters::GaussianKernel filter{};

    filter.process(&image[0], width, height, output);

    uint8_t expected[] = {
        69, 115, 139, 115, 139, 115, 139, 115, 139, 185,
        69, 115, 139, 115, 139, 115, 139, 115, 139, 185,
        69, 115, 139, 115, 139, 115, 139, 115, 139, 185,
        69, 115, 139, 115, 139, 115, 139, 115, 139, 185,
        69, 115, 139, 115, 139, 115, 139, 115, 139, 185,
        69, 115, 139, 115, 139, 115, 139, 115, 139, 185,
        69, 115, 139, 115, 139, 115, 139, 115, 139, 185,
        69, 115, 139, 115, 139, 115, 139, 115, 139, 185,
        69, 115, 139, 115, 139, 115, 139, 115, 139, 185,
        69, 115, 139, 115, 139, 115, 139, 115, 139, 185,
    };

    for (int i = 0; i < width*height; ++i)
        EXPECT_EQ(expected[i], output[i]);
}
