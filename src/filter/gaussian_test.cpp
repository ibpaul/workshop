#include <gtest/gtest.h>
#include "image/patterns.h"
#include "filter/gaussian.h"
#include "filter/operations.h"

using lts::filter::KernelFast;
using lts::filter::Kernel;
using lts::filter::load_gaussian;
using lts::filter::convolute;


TEST(gaussian_test, KernelFast3x3_MockGaussianFilter_VerticalLinesPattern10x10x1) {
    // Test a KernelFast<float,3,3> filled with a mock gaussian filter on a 10x10x1 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 1;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    KernelFast<float, 3, 3> k;
    k.w[0][0] = 1.0f / 11.0f;
    k.w[0][1] = 1.0f / 11.0f;
    k.w[0][2] = 1.0f / 11.0f;
    k.w[1][0] = 1.0f / 11.0f;
    k.w[1][1] = 3.0f / 11.0f;
    k.w[1][2] = 1.0f / 11.0f;
    k.w[2][0] = 1.0f / 11.0f;
    k.w[2][1] = 1.0f / 11.0f;
    k.w[2][2] = 1.0f / 11.0f;

    convolute(k, &image[0], height, width, channels, output);

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

    for (int i = 0; i < width*height*channels; ++i)
        EXPECT_EQ(expected[i], output[i]);
}


TEST(gaussian_test, Kernel3x3_MockGaussianFilter_VerticalLinesImage10x10x1) {
    // Test a Kernel<float> filled with a mock gaussian filter on a 10x10x1 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 1;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    Kernel<float> k {3, 3};
    k.at(0, 0) = 1.0f / 11.0f;
    k.at(0, 1) = 1.0f / 11.0f;
    k.at(0, 2) = 1.0f / 11.0f;
    k.at(1, 0) = 1.0f / 11.0f;
    k.at(1, 1) = 3.0f / 11.0f;
    k.at(1, 2) = 1.0f / 11.0f;
    k.at(2, 0) = 1.0f / 11.0f;
    k.at(2, 1) = 1.0f / 11.0f;
    k.at(2, 2) = 1.0f / 11.0f;

    convolute(k, &image[0], height, width, channels, output);

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

    for (int i = 0; i < width*height*channels; ++i)
        EXPECT_EQ(expected[i], output[i]);
}


TEST(gaussian_test, KernelFast3x3_MockGaussianFilter_VerticalLinesPattern10x10x3) {
    // Test a KernelFast<float,3,3> filled with a mock gaussian filter on a 10x10x3 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 3;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    KernelFast<float, 3, 3> k;
    k.w[0][0] = 1.0f / 11.0f;
    k.w[0][1] = 1.0f / 11.0f;
    k.w[0][2] = 1.0f / 11.0f;
    k.w[1][0] = 1.0f / 11.0f;
    k.w[1][1] = 3.0f / 11.0f;
    k.w[1][2] = 1.0f / 11.0f;
    k.w[2][0] = 1.0f / 11.0f;
    k.w[2][1] = 1.0f / 11.0f;
    k.w[2][2] = 1.0f / 11.0f;

    convolute(k, &image[0], height, width, channels, output);

    uint8_t expected[] = {
        69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
        69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
        69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
        69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
        69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
        69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
        69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
        69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
        69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
        69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
    };

    for (int i = 0; i < width*height*channels; ++i) {
        EXPECT_EQ(expected[i], output[i]) << "different values at index " << i;;
    }
}


TEST(gaussian_test, Kernel3x3_MockGaussianFilter_VerticalLinesPattern10x10x3) {
    // Test a Kernel<float> filled with a mock gaussian filter on a 10x10x3 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 3;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    Kernel<float> k {3, 3};
    k.at(0, 0) = 1.0f / 11.0f;
    k.at(0, 1) = 1.0f / 11.0f;
    k.at(0, 2) = 1.0f / 11.0f;
    k.at(1, 0) = 1.0f / 11.0f;
    k.at(1, 1) = 3.0f / 11.0f;
    k.at(1, 2) = 1.0f / 11.0f;
    k.at(2, 0) = 1.0f / 11.0f;
    k.at(2, 1) = 1.0f / 11.0f;
    k.at(2, 2) = 1.0f / 11.0f;

    convolute(k, &image[0], height, width, channels, output);

    uint8_t expected[] = {
            69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
            69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
            69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
            69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
            69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
            69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
            69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
            69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
            69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
            69, 69, 69, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 115, 115, 115, 139, 139, 139, 185, 185, 185,
    };

    for (int i = 0; i < width*height*channels; ++i) {
        EXPECT_EQ(expected[i], output[i]) << "different values at index " << i;;
    }
}


TEST(gaussian_test, KernelFast3x3) {
    // Tests loading a KernelFast<float, 3, 3> with our load_gaussian function.

    float expected[3][3] = {
        { 1.96412893e-005f,  0.00176805211, 1.96412893e-005f },
        { 0.00176805211,     0.159154952,   0.00176805211 },
        { 1.96412893e-005f,  0.00176805211, 1.96412893e-005f }
    };

    KernelFast<float, 3, 3> k;

    load_gaussian(k);

    for (int m = 0; m < 3; ++m) {
        for (int n = 0; n < 3; ++n) {
            EXPECT_NEAR(expected[m][n], k.w[m][n], 0.00001);
        }
    }
}


TEST(gaussian_test, Kernel3x3) {
    // Tests loading a KernelFast<float> with our load_gaussian function.

    float expected[3][3] = {
            { 1.96412893e-005f,  0.00176805211, 1.96412893e-005f },
            { 0.00176805211,     0.159154952,   0.00176805211 },
            { 1.96412893e-005f,  0.00176805211, 1.96412893e-005f }
    };

    Kernel<float> k {3, 3};

    load_gaussian(k);

    for (int m = 0; m < 3; ++m) {
        for (int n = 0; n < 3; ++n) {
            EXPECT_NEAR(expected[m][n], k.at(m, n), 0.00001);
        }
    }
}

