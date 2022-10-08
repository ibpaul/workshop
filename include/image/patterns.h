// Functions to create test image patterns.
#ifndef LST_IMAGE_PATTERNS_H
#define LST_IMAGE_PATTERNS_H

#include <memory>

namespace lts {
namespace image {


// Returns an image with vertical lines.
//
// [parameters]
// width - Width of the image.
// height - Height of the image.
// channels - Number of channels in the image.
//
// [return]
// The created image.
std::unique_ptr<uint8_t[]> vertical_lines(size_t width, size_t height, size_t channels);


// Writes to the buffer an image with vertical lines.
//
// [parameters]
// buffer - Location to write the image. Must ensure it is at least width*height*channels size.
// width - Width of the image.
// height - Height of the image.
// channels - Number of channels in the image.
void vertical_lines(uint8_t* buffer, size_t width, size_t height, size_t channels);


// Returns an image with horizontal lines.
//
// [parameters]
// width - Width of the image.
// height - Height of the image.
// channels - Number of channels in the image.
//
// [return]
// The created image.
std::unique_ptr<uint8_t[]> horizontal_lines(size_t width, size_t height, size_t channels);


// Writes to the buffer an image with horizontal lines.
//
// [parameters]
// buffer - Location to write the image. Must ensure it is at least width*height*channels size.
// width - Width of the image.
// height - Height of the image.
// channels - Number of channels in the image.
void horizontal_lines(uint8_t* buffer, size_t width, size_t height, size_t channels);


}
}

#endif //LST_IMAGE_PATTERNS_H
