#include <gtest/gtest.h>
#include "CImg.h"
#include "image/patterns.h"
#include "filter/gaussian.h"
#include "filter/operations.h"

using namespace cimg_library;
using Image = CImg<unsigned char>;
using lts::math::MatrixFast;
using lts::math::Matrix;
using lts::math::MatrixEigen;
using lts::math::IMatrix;
using lts::filter::load_gaussian;
using lts::filter::convolute;
using lts::filter::convolute_threaded;


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


void load_pseudo_gaussian_in_3x3_kernel(IMatrix<float>& kernel)
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


TEST(gaussian_test, MatrixFast3x3_PseudoGaussianFilter_VerticalLinesPattern10x10x1) {
    // Test a MatrixFast<float,3,3> filled with a mock gaussian filter on a 10x10x1 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 1;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    MatrixFast<float, 3, 3> k;
    load_pseudo_gaussian_in_3x3_kernel(k);

    convolute(k, &image[0], height, width, channels, output);

    for (int i = 0; i < width*height*channels; ++i)
        EXPECT_EQ(EXPECTED_PSEUDO_GAUSSIAN_10X10X1[i], output[i]);
}


TEST(gaussian_test, Matrix3x3_PseudoGaussianFilter_VerticalLinesImage10x10x1) {
    // Test a Matrix<float> filled with a mock gaussian filter on a 10x10x1 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 1;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    Matrix<float> k {3, 3};
    load_pseudo_gaussian_in_3x3_kernel(k);

    convolute(k, &image[0], height, width, channels, output);

    for (int i = 0; i < width*height*channels; ++i)
        EXPECT_EQ(EXPECTED_PSEUDO_GAUSSIAN_10X10X1[i], output[i]);
}


TEST(gaussian_test, MatrixEigen3x3_PseudoGaussianFilter_VerticalLinesImage10x10x1) {
    // Test a MatrixEigen<float> filled with a mock gaussian filter on a 10x10x1 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 1;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    MatrixEigen<float> k {3, 3};
    load_pseudo_gaussian_in_3x3_kernel(k);

    convolute(k, &image[0], height, width, channels, output);

    for (int i = 0; i < width*height*channels; ++i)
        EXPECT_EQ(EXPECTED_PSEUDO_GAUSSIAN_10X10X1[i], output[i]);
}


TEST(gaussian_test, MatrixFast3x3_PseudoGaussianFilter_VerticalLinesPattern10x10x3) {
    // Test a MatrixFast<float,3,3> filled with a mock gaussian filter on a 10x10x3 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 3;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    MatrixFast<float, 3, 3> k;
    load_pseudo_gaussian_in_3x3_kernel(k);

    convolute(k, &image[0], height, width, channels, output);

    for (int i = 0; i < width*height*channels; ++i) {
        EXPECT_EQ(EXPECTED_PSEUDO_GAUSSIAN_10X10X3[i], output[i]) << "different values at index " << i;;
    }
}


TEST(gaussian_test, Matrix3x3_PseudoGaussianFilter_VerticalLinesPattern10x10x3) {
    // Test a Matrix<float> filled with a mock gaussian filter on a 10x10x3 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 3;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    Matrix<float> k {3, 3};
    load_pseudo_gaussian_in_3x3_kernel(k);

    convolute(k, &image[0], height, width, channels, output);

    for (int i = 0; i < width*height*channels; ++i) {
        EXPECT_EQ(EXPECTED_PSEUDO_GAUSSIAN_10X10X3[i], output[i]) << "different values at index " << i;;
    }
}


TEST(gaussian_test, MatrixEigen3x3_PseudoGaussianFilter_VerticalLinesPattern10x10x3) {
    // Test a MatrixEigen<float> filled with a mock gaussian filter on a 10x10x3 vertical line test pattern.
    constexpr int width = 10;
    constexpr int height = 10;
    constexpr int channels = 3;

    auto image = lts::image::vertical_lines(width, height, channels);
    uint8_t output[width*height*channels]{};

    MatrixEigen<float> k {3, 3};
    load_pseudo_gaussian_in_3x3_kernel(k);

    convolute(k, &image[0], height, width, channels, output);

    for (int i = 0; i < width*height*channels; ++i) {
        EXPECT_EQ(EXPECTED_PSEUDO_GAUSSIAN_10X10X3[i], output[i]) << "different values at index " << i;;
    }
}


TEST(gaussian_test, MatrixFast3x3) {
    // Tests loading a MatrixFast<float, 3, 3> with our load_gaussian function.
    MatrixFast<float, 3, 3> k;

    load_gaussian(k);

    for (int m = 0; m < 3; ++m) {
        for (int n = 0; n < 3; ++n) {
            EXPECT_NEAR(EXPECTED_3X3_GAUSSIAN[m][n], k.w[m][n], 0.00001);
        }
    }
}


TEST(gaussian_test, Matrix3x3) {
    // Tests loading a Matrix<float> with our load_gaussian function.
    Matrix<float> k {3, 3};

    load_gaussian(k);

    for (int m = 0; m < 3; ++m) {
        for (int n = 0; n < 3; ++n) {
            EXPECT_NEAR(EXPECTED_3X3_GAUSSIAN[m][n], k.at(m, n), 0.00001);
        }
    }
}


TEST(gaussian_test, MatrixEigen3x3) {
    // Tests loading a MatrixEigen<float> with our load_gaussian function.
    MatrixEigen<float> k {3, 3};

    load_gaussian(k);

    for (int m = 0; m < 3; ++m) {
        for (int n = 0; n < 3; ++n) {
            EXPECT_NEAR(EXPECTED_3X3_GAUSSIAN[m][n], k.at(m, n), 0.00001);
        }
    }
}


TEST(gaussian_test, MatrixFast3x3_Gaussian_Peppers) {
    // Verifies our MatrixFast 3x3 gaussian filter processes the data/peppers.png image correctly.
    MatrixFast<float, 3, 3> k;
    Image input("data/peppers.png");
    Image output(input.width(), input.height(), input.depth(), input.spectrum());
    Image expected("data/test/peppers_3x3_gaussian.png");

    load_gaussian(k);
    convolute(k, &input[0], input.height(), input.width(), input.spectrum(), &output[0]);

    EXPECT_TRUE(output == expected);
}


TEST(gaussian_test, Matrix3x3_Gaussian_Peppers) {
    // Verifies our Matrix 3x3 gaussian filter processes the data/peppers.png image correctly.
    Matrix<float> k {3, 3};
    Image input("data/peppers.png");
    Image output(input.width(), input.height(), input.depth(), input.spectrum());
    Image expected("data/test/peppers_3x3_gaussian.png");

    load_gaussian(k);
    convolute(k, &input[0], input.height(), input.width(), input.spectrum(), &output[0]);

    EXPECT_TRUE(output == expected);
}


TEST(gaussian_test, MatrixEigen3x3_Gaussian_Peppers) {
    // Verifies our MatrixEigen 3x3 gaussian filter processes the data/peppers.png image correctly.
    MatrixEigen<float> k {3, 3};
    Image input("data/peppers.png");
    Image output(input.width(), input.height(), input.depth(), input.spectrum());
    Image expected("data/test/peppers_3x3_gaussian.png");

    load_gaussian(k);
    convolute(k, &input[0], input.height(), input.width(), input.spectrum(), &output[0]);

    EXPECT_TRUE(output == expected);
}


void test_peppers_MatrixFast3x3_threaded(size_t numOfThreads)
{
    MatrixFast<float, 3, 3> k;
    Image input("data/peppers.png");
    Image output(input.width(), input.height(), input.depth(), input.spectrum());
    Image expected("data/test/peppers_3x3_gaussian.png");

    load_gaussian(k);
    convolute_threaded(numOfThreads, k, &input[0], input.height(), input.width(), input.spectrum(), &output[0]);

    EXPECT_TRUE(expected == output);
}


void test_peppers_Matrix3x3_threaded(size_t numOfThreads)
{
    Matrix<float> k {3, 3};
    Image input("data/peppers.png");
    Image output(input.width(), input.height(), input.depth(), input.spectrum());
    Image expected("data/test/peppers_3x3_gaussian.png");

    load_gaussian(k);
    lts::filter::convolute_threaded_generic<float>(
        numOfThreads,
        static_cast<IMatrix<float>&>(k),
        &input[0],
        input.height(),
        input.width(),
        input.spectrum(),
        &output[0]
    );

    EXPECT_TRUE(expected == output);
}


void test_peppers_MatrixEigen3x3_threaded(size_t numOfThreads)
{
    MatrixEigen<float> k {3, 3};
    Image input("data/peppers.png");
    Image output(input.width(), input.height(), input.depth(), input.spectrum());
    Image expected("data/test/peppers_3x3_gaussian.png");

    load_gaussian(k);
    lts::filter::convolute_threaded_generic<float>(
        numOfThreads,
        static_cast<IMatrix<float>&>(k),
        &input[0],
        input.height(),
        input.width(),
        input.spectrum(),
        &output[0]
    );

    EXPECT_TRUE(expected == output);
}


TEST(gaussian_test, peppers_MatrixFast3x3_gaussian_one_threaded) {
    // Verifies our 3x3 gaussian filter processes the data/peppers.png image correctly when processed with 1 thread.
    test_peppers_MatrixFast3x3_threaded(1);
}


TEST(gaussian_test, peppers_Matrix3x3_gaussian_one_threaded) {
    // Verifies our Matrix3x3 gaussian filter processes the data/peppers.png image correctly when processed with 1 thread.
    GTEST_SKIP() << "under test functions not fully implemented";
    test_peppers_Matrix3x3_threaded(1);
}


TEST(gaussian_test, peppers_MatrixEigen3x3_gaussian_one_threaded) {
    // Verifies our MatrixEigen3x3 gaussian filter processes the data/peppers.png image correctly when processed with 1 thread.
    GTEST_SKIP() << "under test functions not fully implemented";
    test_peppers_MatrixEigen3x3_threaded(1);
}


TEST(gaussian_test, peppers_MatrixFast3x3_gaussian_two_threads) {
    // Verifies our MatrixFast3x3 gaussian filter processes the data/peppers.png image correctly when processed with 2 threads.
    // NOTE: This ensures that the adjacent work areas include image pixels instead of extending from the edge of the
    //       work area.
    test_peppers_MatrixFast3x3_threaded(2);
}


TEST(gaussian_test, peppers_Matrix3x3_gaussian_two_threads) {
    // Verifies our Matrix3x3 gaussian filter processes the data/peppers.png image correctly when processed with 2 threads.
    // NOTE: This ensures that the adjacent work areas include image pixels instead of extending from the edge of the
    //       work area.
    GTEST_SKIP() << "under test functions not fully implemented";
    test_peppers_Matrix3x3_threaded(2);
}


TEST(gaussian_test, peppers_MatrixEigen3x3_gaussian_two_threads) {
    // Verifies our KernelEigen3x3 gaussian filter processes the data/peppers.png image correctly when processed with 2 threads.
    // NOTE: This ensures that the adjacent work areas include image pixels instead of extending from the edge of the
    //       work area.
    GTEST_SKIP() << "under test functions not fully implemented";
    test_peppers_MatrixEigen3x3_threaded(2);
}


TEST(gaussian_test, peppers_MatrixFast3x3_gaussian_three_threads) {
    // Verifies our MatrixFast3x3 gaussian filter processes the data/peppers.png image correctly when processed with 2 threads.
    // NOTE: Tests if our bound calculations don't skip some rows.
    test_peppers_MatrixFast3x3_threaded(3);
}


TEST(gaussian_test, peppers_Matrix3x3_gaussian_three_threads) {
    // Verifies our Matrix3x3 gaussian filter processes the data/peppers.png image correctly when processed with 2 threads.
    // NOTE: Tests if our bound calculations don't skip some rows.
    GTEST_SKIP() << "under test functions not fully implemented";
    test_peppers_Matrix3x3_threaded(3);
}


TEST(gaussian_test, peppers_MatrixEigen3x3_gaussian_three_threads) {
    // Verifies our MatrixEigen3x3 gaussian filter processes the data/peppers.png image correctly when processed with 2 threads.
    // NOTE: Tests if our bound calculations don't skip some rows.
    GTEST_SKIP() << "under test functions not fully implemented";
    test_peppers_MatrixEigen3x3_threaded(3);
}
