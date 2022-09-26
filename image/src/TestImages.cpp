#include "TestImages.h"

namespace LTS {
namespace image {


std::unique_ptr<uint8_t[]> vertical_lines(size_t width, size_t height)
{
    std::unique_ptr<uint8_t[]> image(new uint8_t[width*height]);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            image[y*width + x] = x % 2 ? 255 : 0;
        }
    }

    return image;
}


}
}
