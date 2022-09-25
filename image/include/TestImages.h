// Functions to create test image patterns.
#ifndef LST_IMAGE_TESTIMAGES_H
#define LST_IMAGE_TESTIMAGES_H

#include <memory>

namespace LTS {
namespace image {

// Returns an image with vertical lines.
//
// [DEV_NOTES]
//  - Would like to return a more defined data type.
//  - Allow specifying the image size.
std::unique_ptr<uint8_t[]> linear_lines();

}
}

#endif //LST_IMAGE_TESTIMAGES_H
