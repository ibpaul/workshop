#include <iostream>
#include "gaussian.h"
#include "basic.h"


int main()
{
	std::cout << "Hell2" << std::endl;
    std::cout << test_func() << std::endl;
    std::cout << test_func2() << std::endl;

    load_image();

    std::cout << "Is it working?" << std::endl;
}
