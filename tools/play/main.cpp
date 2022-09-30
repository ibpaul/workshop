#include <iostream>

// Hide error message reporting from CImg.
#define cimg_verbosity 0
#include "CImg.h"

using namespace std;
using namespace cimg_library;


int main(int argc, char* argv[])
{
    if (argc != 2) {
        cerr << "Please specify a file to play." << endl;
        return 1;
    }

    string filename {argv[1]};

    try {
        CImg<unsigned char> image(filename.c_str());

        CImgDisplay main_disp(image, "Test Image");

        while (!main_disp.is_closed()) {
            main_disp.wait();
        }
    } catch (...) {
        std::cerr << "Unable to open file '" << filename << "'." << endl;
    }
}
