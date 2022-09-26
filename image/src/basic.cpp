#include "CImg.h"
using namespace cimg_library;


int test_func2()
{
    return 44;
}

void load_image()
{
    // TODO: Error handling if file not found or unable to be loaded.
    // TODO: Add PNG support by linking to libpng.
    CImg<unsigned char> image("data/peppers.png");

    CImgDisplay main_disp(image, "Test Image");

    while (!main_disp.is_closed()) {
        main_disp.wait();
    }
}
