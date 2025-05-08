#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>

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

bool is_number(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c)
                                      { return !std::isdigit(c); }) == s.end();
}