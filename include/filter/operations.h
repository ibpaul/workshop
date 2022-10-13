/// @file
/// Common filtering operations.
#ifndef LTS_FILTER_OPERATIONS_H
#define LTS_FILTER_OPERATIONS_H

#include <cstddef>
#include <memory>
#include <future>
#include <vector>
#include <Eigen/Dense>
#include "math/SimpleMatrix.h"


namespace lts {
namespace filter {


/// \brief Performs image-style convolution within a specified work area on the image.
///
/// \param kernel Filtering kernel pre-loaded with weights.
/// \param input Block of image data to process.
/// \param ncols Height of the image.
/// \param nrows Width of the image.
/// \param channels Number of channels in the image (e.g. 1 channel for monochrome, 3 channels for RGB).
/// \param output Output block to store the processed image.
/// \param start_row The row to start processing.
/// \param end_row One past the row which should be processed.
template<template<typename, int, int...> class TMatrix, typename T, int Rows, int Cols>
void convolute_work_area(
    const TMatrix<T, Rows, Cols>& kernel,
    const uint8_t* input,
    size_t ncols,
    size_t nrows,
    size_t channels,
    uint8_t* output,
    size_t start_row,
    size_t end_row)
{
    std::unique_ptr<float[]> new_pixel { new float[channels] };

    // Hopefully the compiler will optimize the inner for loop below for static matrices with
    // sizes known at compile-time. This will be a loop unrolling optimization. You may have
    // to play around with your compiler settings to allow this optimization to be performed.
    const auto krows = Rows == Eigen::Dynamic ? kernel.rows() : Rows;
    const auto kcols = Cols == Eigen::Dynamic ? kernel.cols() : Cols;

    for (size_t y = start_row; y < end_row; ++y) {
        for (size_t x = 0; x < ncols; ++x) {
            std::fill_n(new_pixel.get(), channels, static_cast<float>(0.0f));

            for (int ky = 0; ky < krows; ++ky) {
                for (int kx = 0; kx < kcols; ++kx) {
                    auto kc = kernel(ky, kx);

                    int input_x = static_cast<int>(x - kcols / 2 + kx);
                    int input_y = static_cast<int>(y - krows / 2 + ky);

                    // Adjust input coordinate if kernel is
                    // overhanging the input image's side/top.
                    if (input_x < 0)
                        input_x = 0;
                    else if (input_x >= ncols)
                        input_x = ncols - 1;
                    if (input_y < 0)
                        input_y = 0;
                    else if (input_y >= nrows)
                        input_y = nrows - 1;

                    auto input_pixel = &input[input_y*ncols*channels + input_x*channels];

                    for (int i = 0; i < channels; ++i) {
                        new_pixel[i] += kc * (*(input_pixel + i));
                    }
                }
            }

            for (int i = 0; i < channels; ++i) {
                output[y*ncols*channels + x*channels + i] = static_cast<uint8_t>(new_pixel[i]);
            }
        }
    }
}


/// \brief Performs image-style convolution.
///
/// \param kernel Filtering kernel pre-loaded with weights.
/// \param input Block of image data to process.
/// \param ncols Height of the image.
/// \param nrows Width of the image.
/// \param channels Number of channels in the image (e.g. 1 channel for monochrome, 3 channels for RGB).
/// \param output Output block to store the processed image.
template<template<typename, int, int...> class TMatrix, typename T, int Rows, int Cols>
void convolute(
    const TMatrix<T, Rows, Cols>& kernel,
    const uint8_t* input,
    size_t ncols,
    size_t nrows,
    size_t channels,
    uint8_t* output)
{
    // Just call our general work area function with a work area of the whole image.
    convolute_work_area(
        kernel,
        input,
        ncols,
        nrows,
        channels,
        output,
        0,
        ncols
    );
}


/// \brief Performs image-style convolution with multiple threads.
///
/// \param num_threads Number of threads to use to process.
/// \param kernel Filtering kernel pre-loaded with weights.
/// \param input Block of image data to process.
/// \param ncols Height of the image.
/// \param nrows Width of the image.
/// \param channels Number of channels in the image (e.g. 1 channel for monochrome, 3 channels for RGB).
/// \param output Output block to store the processed image.
template<template<typename, int, int...> class TMatrix, typename T, int Rows, int Cols>
void convolute_threaded(
    size_t num_threads,
    const TMatrix<T, Rows, Cols>& kernel,
    const uint8_t* input,
    size_t ncols,
    size_t nrows,
    size_t channels,
    uint8_t* output
)
{
    std::vector<std::future<void>> funcs;
    for (size_t i = 0; i < num_threads; ++i) {
        funcs.push_back(
            std::move(std::async(
                convolute_work_area<TMatrix, T, Rows, Cols>,
                kernel,
                input,
                ncols,
                nrows,
                channels,
                output,
                nrows * i / num_threads,
                nrows * (i + 1) / num_threads
            )
        ));
    }

    for (auto& future : funcs) {
        future.get();
    }
}


}
}

#endif //LTS_FILTER_OPERATIONS_H
