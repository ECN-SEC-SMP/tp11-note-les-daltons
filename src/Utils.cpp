#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#include "Utils.h"

void newRandomSeed()
{
    std::srand(time(nullptr));
}

int getRandomNumber(int max)
{
    return rand() % (max + 1);
}

void sleep(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}