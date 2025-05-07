#include <cstdlib>
#include <ctime>

#include "Utils.h"

void newRandomSeed()
{
    std::srand(time(nullptr));
}

int getRandomNumber(int max)
{
    return rand() % (max + 1);
}