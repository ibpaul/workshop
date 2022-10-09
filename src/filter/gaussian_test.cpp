#include <gtest/gtest.h>
#include "CImg.h"
#include "image/patterns.h"
#include "filter/gaussian.h"
#include "filter/operations.h"

using namespace cimg_library;
using Image = CImg<unsigned char>;
using lts::filter::KernelFast;
using lts::filter::Kernel;
using lts::filter::KernelEigen;
using lts::filter::IKernel;
using lts::filter::load_gaussian;
using lts::filter::convolute;


uint8_t EXPECTED_PSEUDO_GAUSSIAN_10X10X1[] = {
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


uint8_t EXPECTED_PSEUDO_GAUSSIAN_10X10X3[] = {
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


float EXPECTED_3X3_GAUSSIAN[3][3] = {
    { 1.96412893e-005f,  0.00176805211, 1.96412893e-005f },
    { 0.00176805211,     0.159154952,   0.00176805211 },
    { 1.96412893e-005f,  0.00176805211, 1.96412893e-005f }
};


void load_pseudo_gaussian_in_3x3_kernel(IKernel<float>& kernel)
{
    kernel.at(0, 0) = 1.0f / 11.0f;
    kernel.at(0, 1) = 1.0f / 11.0f;
    kernel.at(0, 2) = 1.0f / 11.0f;
    kernel.at(1, 0) = 1.0f / 11.0f;
    kernel.at(1, 1) = 3.0f / 11.0f;
    kernel.at(1, 2) = 1.0f / 11.0f;
    kernel.at(2, 0) = 1.0f / 11.0f;
    kernel.at(2, 1) = 1.0f / 11.0f;
    kernel.at(2, 2) = 1.0f / 11.0f;
}


TEST(gaussian_test, KernelFast3x3_PseudoGaussianFilter_VerticalLinesPattern10x10x1) {
    // Test a KernelFast<float,3,3> filled with a mock gaussian filter on a 10x10x1 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 1;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    KernelFast<float, 3, 3> k;
    load_pseudo_gaussian_in_3x3_kernel(k);

    convolute(k, &image[0], height, width, channels, output);

    for (int i = 0; i < width*height*channels; ++i)
        EXPECT_EQ(EXPECTED_PSEUDO_GAUSSIAN_10X10X1[i], output[i]);
}


TEST(gaussian_test, Kernel3x3_PseudoGaussianFilter_VerticalLinesImage10x10x1) {
    // Test a Kernel<float> filled with a mock gaussian filter on a 10x10x1 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 1;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    Kernel<float> k {3, 3};
    load_pseudo_gaussian_in_3x3_kernel(k);

    convolute(k, &image[0], height, width, channels, output);

    for (int i = 0; i < width*height*channels; ++i)
        EXPECT_EQ(EXPECTED_PSEUDO_GAUSSIAN_10X10X1[i], output[i]);
}


TEST(gaussian_test, KernelEigen3x3_PseudoGaussianFilter_VerticalLinesImage10x10x1) {
    // Test a KernelEigen<float> filled with a mock gaussian filter on a 10x10x1 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 1;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    KernelEigen<float> k {3, 3};
    load_pseudo_gaussian_in_3x3_kernel(k);

    convolute(k, &image[0], height, width, channels, output);

    for (int i = 0; i < width*height*channels; ++i)
        EXPECT_EQ(EXPECTED_PSEUDO_GAUSSIAN_10X10X1[i], output[i]);
}


TEST(gaussian_test, KernelFast3x3_PseudoGaussianFilter_VerticalLinesPattern10x10x3) {
    // Test a KernelFast<float,3,3> filled with a mock gaussian filter on a 10x10x3 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 3;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    KernelFast<float, 3, 3> k;
    load_pseudo_gaussian_in_3x3_kernel(k);

    convolute(k, &image[0], height, width, channels, output);

    for (int i = 0; i < width*height*channels; ++i) {
        EXPECT_EQ(EXPECTED_PSEUDO_GAUSSIAN_10X10X3[i], output[i]) << "different values at index " << i;;
    }
}


TEST(gaussian_test, Kernel3x3_PseudoGaussianFilter_VerticalLinesPattern10x10x3) {
    // Test a Kernel<float> filled with a mock gaussian filter on a 10x10x3 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 3;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    Kernel<float> k {3, 3};
    load_pseudo_gaussian_in_3x3_kernel(k);

    convolute(k, &image[0], height, width, channels, output);

    for (int i = 0; i < width*height*channels; ++i) {
        EXPECT_EQ(EXPECTED_PSEUDO_GAUSSIAN_10X10X3[i], output[i]) << "different values at index " << i;;
    }
}


TEST(gaussian_test, KernelEigen3x3_PseudoGaussianFilter_VerticalLinesPattern10x10x3) {
    // Test a KernelEigen<float> filled with a mock gaussian filter on a 10x10x3 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 3;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    KernelEigen<float> k {3, 3};
    load_pseudo_gaussian_in_3x3_kernel(k);

    convolute(k, &image[0], height, width, channels, output);

    for (int i = 0; i < width*height*channels; ++i) {
        EXPECT_EQ(EXPECTED_PSEUDO_GAUSSIAN_10X10X3[i], output[i]) << "different values at index " << i;;
    }
}


TEST(gaussian_test, KernelFast3x3) {
    // Tests loading a KernelFast<float, 3, 3> with our load_gaussian function.
    KernelFast<float, 3, 3> k;

    load_gaussian(k);

    for (int m = 0; m < 3; ++m) {
        for (int n = 0; n < 3; ++n) {
            EXPECT_NEAR(EXPECTED_3X3_GAUSSIAN[m][n], k.w[m][n], 0.00001);
        }
    }
}


TEST(gaussian_test, Kernel3x3) {
    // Tests loading a Kernel<float> with our load_gaussian function.
    Kernel<float> k {3, 3};

    load_gaussian(k);

    for (int m = 0; m < 3; ++m) {
        for (int n = 0; n < 3; ++n) {
            EXPECT_NEAR(EXPECTED_3X3_GAUSSIAN[m][n], k.at(m, n), 0.00001);
        }
    }
}


TEST(gaussian_test, KernelEigen3x3) {
    // Tests loading a KernelEigen<float> with our load_gaussian function.
    KernelEigen<float> k {3, 3};

    load_gaussian(k);

    for (int m = 0; m < 3; ++m) {
        for (int n = 0; n < 3; ++n) {
            EXPECT_NEAR(EXPECTED_3X3_GAUSSIAN[m][n], k.at(m, n), 0.00001);
        }
    }
}


TEST(gaussian_test, KerenlFast3x3_Gaussian_Peppers) {
    // Verifies our KernelFast 3x3 gaussian filter processes the data/peppers.png image correctly.
    KernelFast<float, 3, 3> k;
    Image input("data/peppers.png");
    Image output(input.width(), input.height(), input.depth(), input.spectrum());
    Image expected("data/test/peppers_3x3_gaussian.png");

    load_gaussian(k);
    convolute(k, &input[0], input.height(), input.width(), input.spectrum(), &output[0]);

    EXPECT_TRUE(output == expected);
}


TEST(gaussian_test, Kerenl3x3_Gaussian_Peppers) {
    // Verifies our Kernel 3x3 gaussian filter processes the data/peppers.png image correctly.
    Kernel<float> k {3, 3};
    Image input("data/peppers.png");
    Image output(input.width(), input.height(), input.depth(), input.spectrum());
    Image expected("data/test/peppers_3x3_gaussian.png");

    load_gaussian(k);
    convolute(k, &input[0], input.height(), input.width(), input.spectrum(), &output[0]);

    EXPECT_TRUE(output == expected);
}


TEST(gaussian_test, KerenlEigen3x3_Gaussian_Peppers) {
    // Verifies our KernelEigen 3x3 gaussian filter processes the data/peppers.png image correctly.
    KernelEigen<float> k {3, 3};
    Image input("data/peppers.png");
    Image output(input.width(), input.height(), input.depth(), input.spectrum());
    Image expected("data/test/peppers_3x3_gaussian.png");

    load_gaussian(k);
    convolute(k, &input[0], input.height(), input.width(), input.spectrum(), &output[0]);

    EXPECT_TRUE(output == expected);
}


void test_peppers_KernelFast3x3_threaded(size_t numOfThreads)
{
    KernelFast<float, 3, 3> k;
    Image input("data/peppers.png");
    Image output(input.width(), input.height(), input.depth(), input.spectrum());
    Image expected("data/test/peppers_3x3_gaussian.png");

    load_gaussian(k);
    convolute_threaded(numOfThreads, k, &input[0], input.height(), input.width(), input.spectrum(), &output[0]);

    EXPECT_TRUE(expected == output);
}


void test_peppers_Kernel3x3_threaded(size_t numOfThreads)
{
    Kernel<float> k {3, 3};
    Image input("data/peppers.png");
    Image output(input.width(), input.height(), input.depth(), input.spectrum());
    Image expected("data/test/peppers_3x3_gaussian.png");

    load_gaussian(k);
    lts::filter::convolute_threaded_generic<float>(
        numOfThreads,
        static_cast<IKernel<float>&>(k),
        &input[0],
        input.height(),
        input.width(),
        input.spectrum(),
        &output[0]
    );

    EXPECT_TRUE(expected == output);
}


void test_peppers_KernelEigen3x3_threaded(size_t numOfThreads)
{
    KernelEigen<float> k {3, 3};
    Image input("data/peppers.png");
    Image output(input.width(), input.height(), input.depth(), input.spectrum());
    Image expected("data/test/peppers_3x3_gaussian.png");

    load_gaussian(k);
    lts::filter::convolute_threaded_generic<float>(
        numOfThreads,
        static_cast<IKernel<float>&>(k),
        &input[0],
        input.height(),
        input.width(),
        input.spectrum(),
        &output[0]
    );

    EXPECT_TRUE(expected == output);
}


TEST(gaussian_test, peppers_KernelFast3x3_gaussian_one_threaded) {
    // Verifies our 3x3 gaussian filter processes the data/peppers.png image correctly when processed with 1 thread.
    test_peppers_KernelFast3x3_threaded(1);
}


TEST(gaussian_test, peppers_Kernel3x3_gaussian_one_threaded) {
    // Verifies our Kernel3x3 gaussian filter processes the data/peppers.png image correctly when processed with 1 thread.
    GTEST_SKIP() << "under test functions not fully implemented";
    test_peppers_Kernel3x3_threaded(1);
}


TEST(gaussian_test, peppers_KernelEigen3x3_gaussian_one_threaded) {
    // Verifies our KernelEigen3x3 gaussian filter processes the data/peppers.png image correctly when processed with 1 thread.
    GTEST_SKIP() << "under test functions not fully implemented";
    test_peppers_KernelEigen3x3_threaded(1);
}


TEST(gaussian_test, peppers_KernelFast3x3_gaussian_two_threads) {
    // Verifies our KernelFast3x3 gaussian filter processes the data/peppers.png image correctly when processed with 2 threads.
    // NOTE: This ensures that the adjacent work areas include image pixels instead of extending from the edge of the
    //       work area.
    test_peppers_KernelFast3x3_threaded(2);
}


TEST(gaussian_test, peppers_Kernel3x3_gaussian_two_threads) {
    // Verifies our Kernel3x3 gaussian filter processes the data/peppers.png image correctly when processed with 2 threads.
    // NOTE: This ensures that the adjacent work areas include image pixels instead of extending from the edge of the
    //       work area.
    GTEST_SKIP() << "under test functions not fully implemented";
    test_peppers_Kernel3x3_threaded(2);
}


TEST(gaussian_test, peppers_KernelEigen3x3_gaussian_two_threads) {
    // Verifies our KernelEigen3x3 gaussian filter processes the data/peppers.png image correctly when processed with 2 threads.
    // NOTE: This ensures that the adjacent work areas include image pixels instead of extending from the edge of the
    //       work area.
    GTEST_SKIP() << "under test functions not fully implemented";
    test_peppers_KernelEigen3x3_threaded(2);
}


TEST(gaussian_test, peppers_KernelFast3x3_gaussian_three_threads) {
    // Verifies our KernelFast3x3 gaussian filter processes the data/peppers.png image correctly when processed with 2 threads.
    // NOTE: Tests if our bound calculations don't skip some rows.
    test_peppers_KernelFast3x3_threaded(3);
}


TEST(gaussian_test, peppers_Kernel3x3_gaussian_three_threads) {
    // Verifies our Kernel3x3 gaussian filter processes the data/peppers.png image correctly when processed with 2 threads.
    // NOTE: Tests if our bound calculations don't skip some rows.
    GTEST_SKIP() << "under test functions not fully implemented";
    test_peppers_Kernel3x3_threaded(3);
}


TEST(gaussian_test, peppers_KernelEigen3x3_gaussian_three_threads) {
    // Verifies our KernelEigen3x3 gaussian filter processes the data/peppers.png image correctly when processed with 2 threads.
    // NOTE: Tests if our bound calculations don't skip some rows.
    GTEST_SKIP() << "under test functions not fully implemented";
    test_peppers_KernelEigen3x3_threaded(3);
}
