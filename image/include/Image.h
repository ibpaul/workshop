// An image.
//
// [DEV NOTES]
// - Would like to fully wrap the underlying CImg library and hide it from the interface/header.

#ifndef WORKSHOP_IMAGE_H
#define WORKSHOP_IMAGE_H

#include <iostream>

namespace LTS {


class Image
{
public:
    Image(std::string filename);
};


}

#endif //WORKSHOP_IMAGE_H
