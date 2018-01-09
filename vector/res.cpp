#include <iostream>
#include "vector.h"
#include <cstdlib>


int main(int argc, char* argv[])
{
    auto pvec = new(std::nothrow) vector<int, 5>(5, 1, 2, 3, 4, 5);
    vector<int,5>& vec = *pvec;
    for (int n : vec("l"))
    {
        std::cout << n << std::endl;
    }
    std::cout << "hello, world" << std::endl;
    for (int n : vec("r"))
    {
        std::cout << n << std::endl;
    }
    system("pause>nul");
    delete pvec;
    return 0;
}
