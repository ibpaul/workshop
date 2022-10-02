#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

// Hide error message reporting from CImg.
#define cimg_verbosity 0
#include "CImg.h"
#include "util/string.h"
#include "options.h"

using namespace std;
using namespace cimg_library;

using Image = CImg<unsigned char>;


unique_ptr<Image> load_image(const string& file_name);
string image_to_cpp_array(const uint8_t* data, size_t length);


int main(int argc, char* argv[])
{
    auto opts = process_all_options(argc, argv);

    if (opts.operation != Options::Operation::ImageToCpp) {
        cout << "unknown operation" << endl;
        exit(1);
    }

    auto input_file = opts.string_param_0;
    auto output_file = opts.string_param_1;

    unique_ptr<Image> image {load_image(input_file)};

    auto code = image_to_cpp_array((*image).data(), image->width() * image->height());

    ofstream file {output_file, ofstream::out};
    file << code;
    file.close();
}


unique_ptr<Image> load_image(const string& file_name)
{
    try {
        return make_unique<Image>(file_name.c_str());
    } catch (CImgIOException&) {
        cerr << "Unable to open file '" << file_name << "'." << endl;
        exit(1);
    } catch (...) {
        cerr << "Unknown error occurred opening file '" << file_name << "'." << endl;
        exit(1);
    }
}


string image_to_cpp_array(const uint8_t* data, size_t length)
{
    stringstream ss;

    ss << "uint8_t image[] = {" << endl << '\t';

    for (int i = 0; i < length; ++i) {
        ss << "0x" << hex << static_cast<int>(*(data + i));
        if (i+1 < length) {
            ss << ',';
            if (((i+1) % 20) == 0) {
                ss << endl << '\t';
            }
        }
    }

    ss << endl << '}' << endl;

    return ss.str();
}
