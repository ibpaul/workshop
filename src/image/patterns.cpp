#include "image/patterns.h"

namespace lts {
namespace image {


using DeterminePixelValue = uint8_t (*)(size_t y, size_t x, size_t channel);


void _pattern_fill_with_function(uint8_t* buffer, size_t width, size_t height, size_t channels, DeterminePixelValue func)
{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int i = 0; i < channels; ++i) {
                buffer[(y*channels)*width + (x*channels) + i] = func(y, x, i);
            }
        }
    }
}

std::unique_ptr<uint8_t[]> vertical_lines(size_t width, size_t height, size_t channels)
{
    std::unique_ptr<uint8_t[]> image(new uint8_t[width*height*channels]);
    vertical_lines(image.get(), width, height, channels);
    return image;
}


void vertical_lines(uint8_t* buffer, size_t width, size_t height, size_t channels)
{
    auto func = [](size_t y, size_t x, size_t c) -> uint8_t { return x % 2 ? 255 : 0; };
    _pattern_fill_with_function(buffer, width, height, channels, func);
}


std::unique_ptr<uint8_t[]> horizontal_lines(size_t width, size_t height, size_t channels)
{
    std::unique_ptr<uint8_t[]> image(new uint8_t[width*height*channels]);
    horizontal_lines(image.get(), width, height, channels);
    return image;
}


void horizontal_lines(uint8_t* buffer, size_t width, size_t height, size_t channels)
{
    auto func = [](size_t y, size_t x, size_t c) -> uint8_t { return y % 2 ? 255 : 0; };
    _pattern_fill_with_function(buffer, width, height, channels, func);
}


}
}
