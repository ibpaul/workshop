#include <gtest/gtest.h>
#include "CImg.h"
#include "image/patterns.h"
#include "filter/gaussian.h"
#include "filter/operations.h"

using namespace cimg_library;
using Image = CImg<unsigned char>;
using Eigen::Matrix;
using Eigen::MatrixX;
using lts::filter::load_gaussian;
using lts::filter::convolute;
using lts::filter::convolute_work_area;


TEST(operations_test, ConvoluteWorkArea_Matrix3x3) {
    // Test that a Matrix<float, 3, 3> run on a work area will use available pixel data on the edges of the work area.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 1;
    constexpr size_t start_row = 3;
    constexpr size_t end_row = 6;

    auto image = lts::image::horizontal_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    Matrix<float, 3, 3> k;
    k(0, 0) = 1.0f / 11.0f;
    k(0, 1) = 1.0f / 11.0f;
    k(0, 2) = 1.0f / 11.0f;
    k(1, 0) = 1.0f / 11.0f;
    k(1, 1) = 3.0f / 11.0f;
    k(1, 2) = 1.0f / 11.0f;
    k(2, 0) = 1.0f / 11.0f;
    k(2, 1) = 1.0f / 11.0f;
    k(2, 2) = 1.0f / 11.0f;

    convolute_work_area(k, &image[0], height, width, channels, output, start_row, end_row);

    uint8_t expected[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        115, 115, 115, 115, 115, 115, 115, 115, 115, 115,
        139, 139, 139, 139, 139, 139, 139, 139, 139, 139,
        115, 115, 115, 115, 115, 115, 115, 115, 115, 115,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    for (int i = 0; i < width*height*channels; ++i)
        EXPECT_EQ(expected[i], output[i]);
}

TEST(operations_test, ConvoluteWorkArea_MatrixX3x3) {
    // Test that a MatrixX<float> run on a work area will use available pixel data on the edges of the work area.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 1;
    constexpr size_t start_row = 3;
    constexpr size_t end_row = 6;

    auto image = lts::image::horizontal_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    MatrixX<float> k {3, 3};
    k(0, 0) = 1.0f / 11.0f;
    k(0, 1) = 1.0f / 11.0f;
    k(0, 2) = 1.0f / 11.0f;
    k(1, 0) = 1.0f / 11.0f;
    k(1, 1) = 3.0f / 11.0f;
    k(1, 2) = 1.0f / 11.0f;
    k(2, 0) = 1.0f / 11.0f;
    k(2, 1) = 1.0f / 11.0f;
    k(2, 2) = 1.0f / 11.0f;

    convolute_work_area(k, &image[0], height, width, channels, output, start_row, end_row);

    uint8_t expected[] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            115, 115, 115, 115, 115, 115, 115, 115, 115, 115,
            139, 139, 139, 139, 139, 139, 139, 139, 139, 139,
            115, 115, 115, 115, 115, 115, 115, 115, 115, 115,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    for (int i = 0; i < width*height*channels; ++i)
        EXPECT_EQ(expected[i], output[i]);
}
