#include <iostream>

// Hide error message reporting from CImg.
//#define cimg_verbosity 0
#include "CImg.h"
#include "util/string.h"

using namespace std;
using namespace cimg_library;


void display_image(const string& filename);
void play_sound(const string& filename);


string get_file_extension(const string& filename)
{
    return lts::util::split(filename, '.').back();
}


int main(int argc, char* argv[])
{
    if (argc != 2) {
        cerr << "Please specify a file to play." << endl;
        return 1;
    }

    string filename {argv[1]};
    auto ext = get_file_extension(filename);

    if (ext == "png") {
        display_image(filename);
    } else if (ext == "wav") {
        play_sound(filename);
    } else {
        cerr << "Unrecognized file type." << endl;
        exit(1);
    }
}


void play_sound(const string& filename)
{

}


void display_image(const string& filename)
{
    try {
        CImg<unsigned char> image(filename.c_str());

        CImgDisplay main_disp(image, "Test Image");

        while (!main_disp.is_closed()) {
            main_disp.wait();
        }
    } catch (...) {
        cerr << "Unable to open file '" << filename << "'." << endl;
        exit(1);
    }
}
