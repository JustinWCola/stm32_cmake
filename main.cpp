#include <iostream>
#include <static_lib.h>

int main()
{
    std::cout << "Hello, CMake!" << std::endl;
    static_lib::print();
    return 0;
}
