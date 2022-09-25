#include "TestImages.h"

namespace LTS {
namespace image {

std::unique_ptr<uint8_t[]> linear_lines()
{
    std::unique_ptr<uint8_t[]> image {new uint8_t[10*10]};

    for (int j = 0; j < 10; ++j) {
        for (int i = 0; i < 10; ++i) {
            image[j*10 + i] = i % 2 ? 255 : 0;
        }
    }

    return image;
}

}
}
