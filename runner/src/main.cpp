#include <iostream>
#include "gaussian.h"
#include "basic.h"
#include "TestImages.h"


int main()
{
	std::cout << "Hell2" << std::endl;
    std::cout << test_func() << std::endl;
    std::cout << test_func2() << std::endl;

    auto test = LTS::image::vertical_lines(10, 10);

    load_image();

    std::cout << "Is it working?" << std::endl;
}
