#include "image/TestImages.h"

namespace LTS {
namespace image {


std::unique_ptr<uint8_t[]> vertical_lines(size_t width, size_t height, int channels)
{
    std::unique_ptr<uint8_t[]> image(new uint8_t[width*height*channels]);
    vertical_lines(image.get(), width, height, channels);
    return image;
}


void vertical_lines(uint8_t* buffer, size_t width, size_t height, int channels)
{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int i = 0; i < channels; ++i) {
                buffer[(y*channels)*width + (x*channels) + i] = x % 2 ? 255 : 0;
            }
        }
    }
}


}
}
