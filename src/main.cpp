#include <iostream>
#include "QuarterBoardHelper.h"

int main(int argc, char const *argv[])
{
    std::cout << "Hello, World!" << std::endl;
    printQuarter(Quarter1);
    std::cout << "------------------------" << std::endl;
    QuarterBoard quarter1_reverse = Quarter1.ApplySymmetry();
    printQuarter(quarter1_reverse);

    return 0;
}
