#include "CImg.h"
using namespace cimg_library;


int main()
{
    CImg<unsigned char> image("data/peppers.png");

    CImgDisplay main_disp(image, "Test Image");

    while (!main_disp.is_closed()) {
        main_disp.wait();
    }
}
